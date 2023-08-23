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
    for(int posDegrees = 0; posDegrees <= 135; posDegrees++) {
        this->servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(10);
        
        
    }
    this->voir_ouverture();
    
    this->ouverture = true;

}
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