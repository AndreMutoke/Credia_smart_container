// Animates white pixels to simulate flying through a star field
#include "main.hpp"
int niveauPoubelle[MAX_LEVELMOYENNE];

Bat_Sound *bouche = new Bat_Sound(12, 13); // trig, echo
Couvercle couv(4, 5); // La broche 4 c'est pour la commande du moteur
//                        La broche 5 c'est pour la LED voyante

long present = 0;  long present2=0; // Pour gerer le temps du programme

int sensorInfrared = 14; int detection; // Pour detecter la presence des personnes


int moyenne =0; // On envoie une moyenne de 30 detection de niveau
int pos = 0; // pour gerer le tableau des moyennes


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

  if((millis() - present )  >= 50)
  {
    // chaque 0,05 seconde on verifie si la poubelle est ouverte
    if(couv.getStateCouvercle()) // True : La poubelle est ouverte;      False :  La poubelle est fermee
    {
      // ============================== Ici la poubelle est ouverte ====================================

      // Envoie le niveau de la poubelle a l'utilisateur le dernier etat de la poubelle
      Serial.println("Envoie le niveau de la poubelle ouverte a l'utilisateur le dernier etat de la poubelle");
      // sendMoyenne(moyenne);
    }
    else {
      // La poubelle est fermee
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
        Serial.println("On envoie la moyenne des niiveua a l'utilisateur");
        moyenne = moyenneNiveau(niveauPoubelle);  initNiveau(niveauPoubelle);
        
        // sendMoyenne(moyenne);
        if(bouche->dist_limit())
        {
          Serial.println("Envoie du code rouge");
          // Envoie du code rouge
          
        }
        
      }

      // ===================== On verifie aussi qui se trouve devant la poubelle ==============================
      if((millis() - present2 )  >= 50)
      {
        // On verifie chaque 0,05 secondes les personne est  devant
        Serial.println("On verifie chaque 0,05 secondes les personne est  devant");
        detection = digitalRead(sensorInfrared);
        if(detection == 1)
        {
          // Une personne est detectee
          Serial.println("Une personne est detectee");
          // On ouvre la poubelle puis on la ferme apres 7,5 secondes
          couv.ouvrir_couvercle();
          delay(7500);
          couv.fermer_couvercle();

        }
        present2 = millis();
        
      }
      // +++++++++++++++++++ DHT DETECTION D'HUMIDITE ++++++++++++++++++++++++

      // ++++++++++++++++++++++ DETECTION DE TEMPERATURE ++++++++++++++++++++++++      
      
    }
    present = millis();
  }
  delay(2000); 
}