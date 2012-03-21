/* 
 * File:   BeerBuddyRfid.h
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
 * 
 * Created on March 21, 2012, 4:12 PM
 */

#ifndef BEERBUDDYUSER_H
#define	BEERBUDDYUSER_H

#include "../../hardware/arduino/cores/arduino/Arduino.h"

class BeerBuddyUser
{
public:
    BeerBuddyUser();
    void parse(char* response);
    bool isValid();
    char* getUserid();
    char* getUsername();
private:
    int i;
    int strLen;
    int pipe;
    int ui;
    bool valid;
    char userid[4];
    char username[20];
};

#endif	/* BEERBUDDYUSER_H */