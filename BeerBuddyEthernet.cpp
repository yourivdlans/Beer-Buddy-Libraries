/* 
 * File:   BeerBuddyEthernet.cpp
 * Author: Pim Vogels & Youri van der Lans
 * 
 * Created on February 22, 2012, 1:04 PM
 */

#include "BeerBuddyEthernet.h"

EthernetClient client;

BeerBuddyEthernet::BeerBuddyEthernet(byte* mac, IPAddress ip, char* name) :
  startTime(0),
  keepAliveInterval(120000)
{
  //byte macAddress[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x03, 0x05 };
  //serverIp = {85,214,92,47}; // beer-buddy.nl
  //char serverName[] = "http://beer-buddy.nl";
  
  macAddress = mac;
  serverIp = ip;
  serverName = name;
  
  startTime = millis();
}

BeerBuddyEthernet::~BeerBuddyEthernet()
{
  
}

// Public
void
BeerBuddyEthernet::initialize()
{
  Serial.println("Starting...");
  
  Serial.println(serverIp);
  Serial.println(serverName);
  
  // start the Ethernet connection:
  Ethernet.begin(macAddress);
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  
  Serial.println("Arduino IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);  
    Serial.print(".");
  }
  
  Serial.println();
}

void
BeerBuddyEthernet::enableKeepAlive()
{
  if((millis() - startTime) > keepAliveInterval)
  {
    startTime = millis();
    keepAlive();
  }
}

void
BeerBuddyEthernet::setOnline()
{
  Serial.println("setOnline");
  
  char url[] = "GET http://beer-buddy.nl/api/online HTTP/1.0";
  
  sendRequest(url);
}

void
BeerBuddyEthernet::sendRFID(char rfid[])
{
  Serial.println("sendRFID");
  
  char url[] = "GET http://beer-buddy.nl/api/rfid/4B00DA184BC2 HTTP/1.0";
  
  sendRequest(url);
}

void
BeerBuddyEthernet::keepAlive()
{
  Serial.println("keepAlive");
  
  if (client.connect(serverIp, 80))
  {
    client.println("GET http://beer-buddy.nl/api HTTP/1.0");
    client.println();
  } 
  else
  {
    Serial.println("connection failed");
    Serial.println();
  }
  
  client.stop();
}

// Private
void
BeerBuddyEthernet::sendRequest(char url[])
{
  Serial.println("sendRequest");
  
  Serial.println(url);
  
  if (client.connect(serverIp, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println(url);
    client.println();
  } 
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  Serial.print("Server Response => ");
  
  while(client.connected() && !client.available()) delay(1); //waits for data
  while(client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
    Serial.print(c); //prints byte to serial monitor 
  }

  Serial.println();
  Serial.println("disconnecting.");
  Serial.println("==================");
  Serial.println();
  
  client.stop();
}