// Animates white pixels to simulate flying through a star field
#include "main.hpp"
int niveauPoubelle[MAX_LEVELMOYENNE];

Bat_Sound *bouche = new Bat_Sound(12, 13); // trig, echo
Couvercle couv(4, 5); // La broche 4 c'est pour la commande du moteur
//                        La broche 5 c'est pour la LED voyante

long present = 0;  long present2=0; // Pour gerer le temps du programme

int sensorInfrared = 14; int detection; // Pour detecter la presence des personnes



int moyenne = 0; // On envoie une moyenne de 30 detection de niveau

int pos = 0; // pour gerer le tableau des moyennes

//=================NEW===================
bool openingCave = false; //COUVERCLE EN COURS D'OUVERTURE
bool closingCave = false; // COUVERCLE EN COURS DE FERMETURE
unsigned int delayCave[] = {50, 15000};
unsigned short delayActionCouvercle = 10; //delai avant chaque action sur le couvercle(incrementation ou de crementation de position de ce dernier )
unsigned long currentTimeActionCouvercle = 0; //temps courant lors de l'ouverture ou fermeture de la poubelle
//delayCave[0]: delai avant reverification de l'etat du couvercle
//delayCave[1]: delai d'ouverture du couvercle

void setup(){
  // =======================  On initialise tout les necessaire =========================
  Serial.begin(115200);  // ============= Communication serie
  bouche->begin(); // ========== Le capteur Ultra son
  couv.begin(); // ======= Le couvercle de la poubelle

  Serial.println("La poubeelle begin()"); 
  initNiveau(niveauPoubelle); // On initialise tout  a  0
  pinMode(sensorInfrared, INPUT); // Pour lire l'etat de la sortie

  // ++++++++++++ POUR INITIALISER LE WIFI +++++++++++++++++++++

}
void loop(){
  //SI LE COUVERCLE EST OUVERT ET QU'IL N'EST PAS EN COURS DE FERMETURE, ALORS ON VERIFIE SI LE DELAI D'OUVERTURE EST EPUISE
  if(couv.getStateCouvercle() && !closingCave){
    if((millis() - present )  >= delayCave[1]){
      closingCave = !couv.fermer_couvercle(true);
      present = millis();
    }
  }
    //=====================================================================================================================================
    //SI LE COUVERCLE EST FERME ET QU'IL N'EST PAS EN COURS D'OUVERTURE, ALORS ON LIT LE NIVEAU DU CONTENU ET LE DETECTEUR DE PROXIMITE

  if(!couv.getStateCouvercle() && !openingCave){
    if((millis() - present2 )  >= delayCave[0])
    {

      Serial.println("La poubelle est fermee");
      if(pos < MAX_LEVELMOYENNE)
      {
        Serial.println("On enregistre la position");
        niveauPoubelle[pos] = bouche->detect_obstacle_distance(); pos++; // On enregistre la position
      }
      else
      {
        pos = 0;
        // On envoie la moyenne des niiveua a l'utilisateur
        Serial.println("On envoie la moyenne du niveau a l'utilisateur");
        moyenne = moyenneNiveau(niveauPoubelle);  initNiveau(niveauPoubelle);
        
        // sendMoyenne(moyenne);
        if(bouche->dist_limit())
        {
          Serial.println("Envoie du code rouge");
          // Envoie du code rouge
          
        }
      }
      //READ_SENSORS();//FONCTION QUI PERMETTRA DE LIRE L'ETAT DES TOUS LES CAPTEURS EN PRENANT EN COMPTE SI LA POUBELLE EST OUVERTE OU NON
      detection = digitalRead(sensorInfrared);
      if(detection == 1)
      {
        openingCave = !(couv.ouvrir_couvercle(true));
        currentTimeActionCouvercle = millis();
      }
      present2 = millis();
    }

    //===================LOGIQUE D'OUVERTURE AVEC MILLIS==================
    if(openingCave){
      if(millis() - currentTimeActionCouvercle >= delayActionCouvercle){
        openingCave = !(couv.ouvrir_couvercle(true));
        currentTimeActionCouvercle = millis();
      }
    }
    //===================LOGIQUE DE FERMETURE AVEC MILLIS==================
    if(closingCave){
      if(millis() - currentTimeActionCouvercle >= delayActionCouvercle){
        closingCave = !(couv.fermer_couvercle(true));
        currentTimeActionCouvercle = millis();
      }
    }

    //==============SEND_VALUES_SENSORS????=============================

    // +++++++++++++++++++ DHT DETECTION D'HUMIDITE ++++++++++++++++++++++++

    // ++++++++++++++++++++++ DETECTION DE TEMPERATURE ++++++++++++++++++++++++      
    
  }
      
  //delay(2000); 
}