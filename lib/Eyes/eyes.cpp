#include "eyes.hpp"


Eyes::Eyes(int sensor, int pinout)
{
    this->sensor = sensor;
    this->out_put = pinout;
}

void Eyes::begin()
{
    pinMode(this->sensor, INPUT);
    pinMode(this->out_put, OUTPUT);

    this->state_out = LOW;
}

void Eyes::voir_mouvement()
{
    int val = digitalRead(this->sensor); delay(100);

    if(val == HIGH)
    {
        if(this->state_out == LOW) {
            this->state_out = HIGH; 
            this->out_put = this->state_out;
            
        }// On a detecte un truc
        else{
            if( this->state_out == HIGH)
            this->state_out = LOW; // on a rien detecte
            this->out_put = this->state_out;
        }
    }
    
}

