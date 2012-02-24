/* 
 * File:   BeerBuddyRfid.h
 * Author: Youri van der Lans
 *
 * Created on February 21, 2012, 2:24 PM
 */

#ifndef BEERBUDDYRFID_H
#define	BEERBUDDYRFID_H

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "../../hardware/arduino/cores/arduino/Arduino.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/
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
    
    bool result;
    
    BeerBuddyRfid(int red, int green);
    virtual ~BeerBuddyRfid();
    char* getCard();
    bool compareString(char str1[], char str2[], int length);
    bool checkCard();
private:
    char card[12];
    
    void setLed(int pin, int duration);
};

#endif	/* BEERBUDDYRFID_H */

