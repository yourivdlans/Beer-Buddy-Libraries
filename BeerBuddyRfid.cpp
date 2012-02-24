/* 
 * File:   BeerBuddyRfid.cpp
 * Author: Youri van der Lans
 * 
 * Card1: 4000EE36E57D
 * Card2: 4500F6893903
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
BeerBuddyRfid::compareString(char str1[], char str2[], int length)
{
  for ( i=0; i<=length; i++ )
  {
    if ( str1[i] != str2[i] )
    {
      return false;
    }
  }
  
  return true;
}

void
BeerBuddyRfid::setLed(int pin, int duration)
{
  if ( startTime == 0 ){
    digitalWrite(pin, HIGH);
    
    startTime = millis();
  }
  
  long diff = (millis() - startTime);
  
  if ( startTime != 0 && diff >= duration )
  {
    digitalWrite(pin, LOW);
    
    startTime = 0;
    enableLed = 0;
  }
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
  
//  if ( y == 13 ){
//    //Serial.println(i);
//    if ( compareString("4000EE36E57D", card, 11) ){
//      //Serial.println("Access granted!");
//      
//      result = true;
//      
//      enableLed = green;
//    } else {
//      //Serial.println("Access denied!");
//      
//      enableLed = red;
//    }
//    
//    i = 0;
//    y = 0;
//  }
//  
//  if ( enableLed != 0 ){
//    setLed(enableLed, 1000);
//  }
//  
//  return result;
}