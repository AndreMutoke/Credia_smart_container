#include "couvercle.hpp"

Couvercle::Couvercle(int servPin, int pinCtrl)
{
    this->ouverture = false;
    this->pinCtrl = pinCtrl;
    this->servoPin = servPin;
}

void Couvercle::begin()
{
    this->servo1.attach(this->servoPin);
    pinMode(this->pinCtrl, OUTPUT);
    digitalWrite(this->pinCtrl, LOW);
}
void Couvercle::ouvrir_couvercle(){
    for(int posDegrees = MIN_ANGLE; posDegrees <= MAX_ANGLE; posDegrees++) {
        this->servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(10);
        
        
    }
    this->voir_ouverture();
    
    this->ouverture = true;

}

//===============NEW_METHODE=========================================
bool Couvercle::ouvrir_couvercle(bool action){
    static int posServo = MIN_ANGLE; //position du servomoteur en terme d'angle
    this->servo1.write(posServo);
    if(action)
        if(++posServo > MAX_ANGLE){
            posServo = MAX_ANGLE;
            this->ouverture = true;
        }
    this->voyant_couvercle(true);
    return this->ouverture;
}

bool Couvercle::fermer_couvercle(bool action){
    static int posServo = MAX_ANGLE; //position du servomoteur en terme d'angle
    this->servo1.write(posServo);
    if(action)
        if(--posServo < MIN_ANGLE){
            posServo = MIN_ANGLE;
            this->ouverture = false;
        }
    this->voyant_couvercle(false);
    return this->ouverture;

}

//etat du voyant du couvercle
void Couvercle::voyant_couvercle(bool statePinCtrl){
   digitalWrite(this->pinCtrl, statePinCtrl); 
}

//reourne la position du servomoteur et donc l'angle d'ouverture du couvercle
int Couvercle::get_pos_couvercle(){

    return this->servo1.read();
}
//=================================================================

void Couvercle::fermer_couvercle(){
    for(int posDegrees = 136; posDegrees >= 0; posDegrees--) {
        this->servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
        
       
    }
    this->voir_fermeture();
    
    this->ouverture = false;
}
void Couvercle::voir_ouverture(){
    digitalWrite(this->pinCtrl, HIGH); delay(10);
    digitalWrite(this->pinCtrl, LOW); delay(10);
    digitalWrite(this->pinCtrl, HIGH); delay(10);
    digitalWrite(this->pinCtrl, LOW); delay(10);
    digitalWrite(this->pinCtrl, HIGH);
    
}
void Couvercle::voir_fermeture(){
    delay(10);
    digitalWrite(this->pinCtrl, LOW); delay(10);
    digitalWrite(this->pinCtrl, HIGH); delay(10);
    digitalWrite(this->pinCtrl, LOW); delay(10);
    digitalWrite(this->pinCtrl, HIGH);delay(10);
    digitalWrite(this->pinCtrl, LOW);

}