#ifndef COUVERCLE_HPP
#define COUVERCLE_HPP

#include <Arduino.h>
#include <Servo.h>

//=====ACTION SUR LE COUVERCLE=====
#define CLOSE 0x00
#define OPEN 0x01
#define MAX_ANGLE 135
#define MIN_ANGLE 0
class Couvercle
{
public :
    Couvercle(int , int );
    void begin();

    bool getStateCouvercle(){
        return this->ouverture;
    }
    void ouvrir_couvercle();

    void fermer_couvercle();

    void voir_ouverture();
    void voir_fermeture();

//========NEW_METHODE============
    bool ouvrir_couvercle(bool operation);
    bool fermer_couvercle(bool operation);
    void voyant_couvercle(bool statePinCtrl);
    int get_pos_couvercle();


private :
    int servoPin; // La broche de commande d'ouverture et de fermeture du servo
    int pinCtrl; // Lampe temoin de l'ouverture ou la fermeture
    bool ouverture; // L'etat du couvercle true ---> ouvert       false ---> ferme
    Servo servo1;// Le servo moteur

};


#endif // COUVERCLE_HPP