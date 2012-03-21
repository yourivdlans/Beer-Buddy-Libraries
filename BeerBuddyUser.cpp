/* 
 * File:   BeerBuddyEthernet.cpp
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
 * 
 * Created on March 21, 2012, 4:12 PM
 */

#include "BeerBuddyUser.h"

BeerBuddyUser::BeerBuddyUser() :
  i(0),
  strLen(0),
  pipe(0),
  ui(0),
  valid(false)
{
  
}

void
BeerBuddyUser::parse(char* response)
{
  strLen = strlen(response);
  
  if ( response[0] == '1' )
  {
    valid = true;
  }
  else
  {
    valid = false;
  }
  
  for ( i=1; i<strLen; ++i )
  {
    if(response[i] == '|')
    {
      ++pipe;
      ui = 0;
    }
    else
    {
      switch(pipe)
      {
        case 1:
          userid[ui] = response[i];
        break;
        case 2:
          username[ui] = response[i];
        break;
      }
      
      ++ui;
    }
    
  }
}

bool
BeerBuddyUser::isValid()
{
  return valid;
}

char*
BeerBuddyUser::getUserid()
{
  return userid;
}

char*
BeerBuddyUser::getUsername()
{
  return username;
}