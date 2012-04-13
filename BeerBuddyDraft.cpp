/* 
 * File:   BeerBuddyEthernet.cpp
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
 * 
 * Created on March 21, 2012, 4:12 PM
 */

#include "BeerBuddyDraft.h"

Servo GlassServo;
Servo DraftServo;

BeerBuddyDraft::BeerBuddyDraft(int glassServoPin, int draftServoPin) :
  i(0),
  glassDefaultPos(160),
  draftDefaultPos(70),
  currentServoPos(0)
{
  
}

void
BeerBuddyDraft::setupServos()
{
  GlassServo.attach(glassServoPin);
  GlassServo.write(glassDefaultPos);
  
  DraftServo.attach(draftServoPin);
  DraftServo.write(draftDefaultPos);
}

void
BeerBuddyDraft::draftBeer()
{
  delay(1000);
  
  // Move arm up
  moveServo(GlassServo, 110, 15);
  
  // Start drafting
  moveServo(DraftServo, 15, 10);
  
  delay(2000);
  
  // Stop drafting
  moveServo(DraftServo, draftDefaultPos, 10);
  
  // Move arm down
  moveServo(GlassServo, glassDefaultPos, 30);
}

void
BeerBuddyDraft::moveServo(Servo servo, int servoPos, int servoDelay)
{
  currentServoPos = servo.read();
  
  if ( servoPos > currentServoPos )
  {
    for ( i=currentServoPos; i<=servoPos; ++i )
    {
      servo.write(i);
      delay(servoDelay);
    }
  }
  
  if ( servoPos < currentServoPos )
  {
    for ( i=currentServoPos; i>=servoPos; --i )
    {
      servo.write(i);
      delay(servoDelay);
    }
  }
}