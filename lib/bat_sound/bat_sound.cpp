#include "bat_sound.hpp"

#define SOUND_VELCITY 0.0343 // 0.0343 centimetre / microseconde
#define DIST_LIMIT 3 // c'est 3 centimetres

Bat_Sound::Bat_Sound(int trigger, int echo)
{
    this->TRIG_PIN = trigger;
    this->ECHO_PIN = echo;
}
void Bat_Sound::begin()
{
    pinMode(this->TRIG_PIN, OUTPUT);
    pinMode(this->ECHO_PIN, INPUT);
}

void Bat_Sound::emit_pulse()
{
    digitalWrite(this->TRIG_PIN, LOW); delayMicroseconds(5);
    digitalWrite(this->TRIG_PIN, HIGH); delayMicroseconds(10);
    digitalWrite(this->TRIG_PIN, LOW);
        
}
void Bat_Sound::detect_distance()
{
    this->duration = pulseIn(this->ECHO_PIN, HIGH);
    this->distance = (this->duration * SOUND_VELCITY) / 2;
}

long Bat_Sound::detect_obstacle_distance()
{
    this->emit_pulse();
    this->detect_distance();
    return this->distance; // en centimetre
}
bool Bat_Sound::dist_limit()
{
        long val = this->detect_obstacle_distance();
        if(val <= DIST_LIMIT) // Proche de 6 cm
        {
            return true;
        }
        return false;
    }