/* 
 * File:   BeerBuddyRfid.h
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
 *
 * Created on February 21, 2012, 2:24 PM
 */

#ifndef BEERBUDDYRFID_H
#define	BEERBUDDYRFID_H

#include "../../hardware/arduino/cores/arduino/Arduino.h"

#define receivePin 2
#define transmitPin 3

class BeerBuddyRfid
{
public:
    int i;
    int y;
    int enableLed;
    int red;
    int green;

    char incomingByte;

    long startTime;
    
    BeerBuddyRfid(int red, int green);
    virtual ~BeerBuddyRfid();
    char* getCard();
    bool compareChar(char str1[], char str2[], int length);
    bool setLed(int pin, int duration);
    bool checkCard();
private:
    bool result;
    char card[12];
    long runningFor;
};

#endif	/* BEERBUDDYRFID_H */

