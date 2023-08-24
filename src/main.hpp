#ifndef MAIN_HPP
#define MAIN_HPP

#include <Arduino.h>

#include <Servo.h>
#include <bat_sound.hpp>
#include <couvercle.hpp>

#define MAX_LEVELMOYENNE 30


void initNiveau(int niveau[])
{
    for(int i=0; i<MAX_LEVELMOYENNE; ++i)
    {
        niveau[i] = 0;
    }
}

int moyenneNiveau(int niveau[])
{
    int resultat = 0;

    for(int i=0; i<MAX_LEVELMOYENNE; ++i)
    {
        resultat += niveau[i];
    }
    resultat /= MAX_LEVELMOYENNE;

    return resultat;
}

//SI LA DETECTION PREND BRUSQUEMENT(DETECTION D'UNE PERSONNE, ALORS CALCUL DE LA MOYENNE AVEC LE NOMBRE D'ELEMENTS DISPO DANS LE TABLEAU)
int moyenneNiveau(int niveau[], int taille)
{
    int resultat = 0;

    for(int i=0; i< taille; ++i)
    {
        resultat += niveau[i];
    }
    resultat /= taille;

    return resultat;
}

#endif // MAIN_HPP