#ifndef BAT_SOUND_HPP
#define BAT_SOUND_HPP

#include <Arduino.h>




// Manipulation du capteur Ultra son
class Bat_Sound 
{
public :
    Bat_Sound(int trigger = 2, int echo = 3);
    void begin();

    long detect_obstacle_distance();
    bool dist_limit();

    
private :
    int TRIG_PIN; // La pin trigger du HC-SR04
    int ECHO_PIN; // la pin echo du HC-SR04

    long duration; // la duree de l'eccho
    long distance; // la distance calculee

    void emit_pulse();
    void detect_distance();

    


};

#endif // BAT_SOUND_HPP