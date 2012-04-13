/* 
 * File:   BeerBuddyRfid.h
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
 * 
 * Created on March 21, 2012, 4:12 PM
 */

#ifndef BEERBUDDYDRAFT_H
#define BEERBUDDYDRAFT_H

#include "../../hardware/arduino/cores/arduino/Arduino.h"
#include "../Servo/Servo.h"

class BeerBuddyDraft
{
public:
    BeerBuddyDraft(int glassServoPin, int draftServoPin);
    void setupServos();
    void draftBeer();
private:
    int i;
    int glassServoPin;
    int draftServoPin;
    int glassDefaultPos;
    int draftDefaultPos;
    int currentServoPos;
    
    void moveServo(Servo servo, int servoPos, int servoDelay);
};

#endif	/* BEERBUDDYDRAFT_H */