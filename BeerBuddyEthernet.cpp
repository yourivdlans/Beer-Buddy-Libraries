/* 
 * File:   BeerBuddyEthernet.cpp
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
 * 
 * Created on February 22, 2012, 1:04 PM
 */

#include "BeerBuddyEthernet.h"

EthernetClient client;

BeerBuddyEthernet::BeerBuddyEthernet(byte* mac, IPAddress remote_ip, char* name) :
  startTime(0),
  keepAliveInterval(120000),
  bufferLength(200),
  y(0),
  readStream(false),
  localIp(0, 0, 0, 0)
{
  macAddress = mac;
  serverIp = remote_ip;
  serverName = name;
  
  startTime = millis();
}

BeerBuddyEthernet::~BeerBuddyEthernet()
{
  
}

// Public
void
BeerBuddyEthernet::setLocalIp(IPAddress local_ip)
{
  localIp = local_ip;
}

void
BeerBuddyEthernet::initialize()
{
  Serial.println("Starting...");
  
  // start the Ethernet connection:
  if ( localIp != 0 )
  {
    Ethernet.begin(macAddress, localIp);
  }
  else
  {
    Ethernet.begin(macAddress);
  }
  
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
  
  url = createUrl("/api/online");
  
  sendRequest(url);
}

char*
BeerBuddyEthernet::checkOnline()
{
  Serial.println("checkOnline");
  
  url = createUrl("/api/checkServerOnline/raw");
  
  response = sendRequest(url);
  
  return response;
}

char*
BeerBuddyEthernet::sendRFID(char rfid[12])
{
  Serial.println("sendRFID");
  
  String combined = String(String("/api/rfid/") + String(rfid) + String("/raw"));
  combined.toCharArray(buffer, bufferLength);
  
  url = createUrl(buffer);
  
  response = sendRequest(url);
  
  return response;
}

void
BeerBuddyEthernet::keepAlive()
{
  Serial.println("keepAlive");
  
  url = createUrl("/api");
  
  sendRequest(url);
}

// Private
char*
BeerBuddyEthernet::createUrl(char* path)
{
  String url1 = String("GET ");
  String url2 = String(serverName);
  String url3 = String(path);
  String url4 = String(" HTTP/1.0");
  
  String url = String(url1 + url2 + url3 + url4);
  
  url.toCharArray(buffer, bufferLength);
  
  return buffer;
}

char*
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
  
  while(client.connected() && !client.available()) delay(1); //waits for data
  while(client.connected() || client.available())
  { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
    
    if ( readStream )
    {
      requestStream[y] = c;
      ++y;
    }
    
    if ( c == '#' )
    {
      readStream = true;
    }
  }
  
  requestStream[y] = '\0';
  
  y = 0;
  readStream = false;
  
  client.stop();
  
  return requestStream;
}