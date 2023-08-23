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

#endif // MAIN_HPP