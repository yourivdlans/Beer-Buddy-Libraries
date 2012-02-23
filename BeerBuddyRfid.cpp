/* 
 * File:   BeerBuddyRfid.cpp
 * Author: Youri van der Lans
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

BeerBuddyRfid::~BeerBuddyRfid() {
}

char
BeerBuddyRfid::getCard()
{
  return* card;
}

bool
BeerBuddyRfid::compareString(char str1[], char str2[], int length) {
  for ( i=0; i<=length; i++ ){
    if ( str1[i] != str2[i] ){
      return false;
    }
  }
  
  return true;
}

void
BeerBuddyRfid::setLed(int pin, int duration){
  if ( startTime == 0 ){
    digitalWrite(pin, HIGH);
    
    startTime = millis();
  }
  
  long diff = (millis() - startTime);
  
  if ( startTime != 0 && diff >= duration ){
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

      if ( i != 0 && i <= 13 )
      {
        card[y] = incomingByte;
        ++y;
      }

      i++;
    }
  }
  
  if ( y == 13 )
  {
    result = true;
  }
  else
  {
    result = false;
  }
  
  return result;
  
//  if ( y == 13 ){
//    //Serial.println(i);
//    if ( compareString("4B00DA184BC2", card, 11) ){
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