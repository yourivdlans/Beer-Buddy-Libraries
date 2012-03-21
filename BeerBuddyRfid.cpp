/* 
 * File:   BeerBuddyRfid.cpp
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
 * 
 * Created on February 21, 2012, 2:24 PM
 */

#include "../SoftwareSerial/SoftwareSerial.h"

#include "BeerBuddyRfid.h"

SoftwareSerial BeerBuddyRfidStream(receivePin, transmitPin);

//
// Constructor
//
BeerBuddyRfid::BeerBuddyRfid(int red_pin, int green_pin) :
  i(0),
  y(0),
  enableLed(0),
  startTime(0),
  result(false)
{
  BeerBuddyRfidStream.begin(9600);
  
  red = red_pin;
  green = green_pin;
}

BeerBuddyRfid::~BeerBuddyRfid()
{
}

char*
BeerBuddyRfid::getCard()
{
  return card;
}

bool
BeerBuddyRfid::compareChar(char str1[], char str2[], int length)
{
  result = true;
  
  for ( i=0; i<=length; i++ )
  {
    if ( str1[i] != str2[i] )
    {
      result = false;
    }
  }
  
  return result;
}

bool
BeerBuddyRfid::setLed(int pin, int duration)
{
  result = true;
  
  if ( startTime == 0 ){
    digitalWrite(pin, HIGH);
    
    startTime = millis();
  }
  
  runningFor = (millis() - startTime);
  
  if ( startTime != 0 && runningFor >= duration )
  {
    digitalWrite(pin, LOW);
    
    startTime = 0;
    enableLed = 0;
    
    result = false;
  }
  
  return result;
}

bool
BeerBuddyRfid::checkCard()
{
  if ( BeerBuddyRfidStream.available() >= 15 )
  {
    while ( BeerBuddyRfidStream.available() && enableLed == 0 )
    {
      incomingByte = BeerBuddyRfidStream.read();

      if ( i != 0 && i <= 12 )
      {
        card[y] = incomingByte;
        ++y;
        
        if ( y == 12 )
        {
          card[y] = '\0';
        }
      }

      ++i;
    }
  }
  
  if ( y == 12 )
  {
    result = true;
    
    i = 0;
    y = 0;
  }
  else
  {
    result = false;
  }
  
  return result;
}