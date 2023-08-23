#ifndef COUVERCLE_HPP
#define COUVERCLE_HPP

#include <Arduino.h>
#include <Servo.h>


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


private :
    int servoPin; // La broche de commande d'ouverture et de fermeture du servo
    int pinCtrl; // Lampe temoin de l'ouverture ou la fermeture
    bool ouverture; // L'etat du couvercle true ---> ouvert       false ---> ferme
    Servo servo1;// Le servo moteur

};


#endif // COUVERCLE_HPP