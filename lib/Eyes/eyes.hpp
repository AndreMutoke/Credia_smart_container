#ifndef EYES_H
#define EYES_H

#include <Arduino.h>

class Eyes
{
public :
    Eyes(int sensor, int pinout);

    void begin();
    void voir_mouvement();
    
    int getState_out(){
        return this->state_out;
    }
    void setPinOut(int state)
    {
        pinMode(this->out_put,state);
    }

    

private :
    int sensor;
    int out_put;

    int state_out;

};


#endif // EYES_H