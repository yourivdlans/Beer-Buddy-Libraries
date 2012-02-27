/* 
 * File:   BeerBuddyEthernet.h
 * Author: Pim Vogels & Youri van der Lans
 *
 * Created on February 22, 2012, 1:04 PM
 */

#ifndef BEERBUDDYETHERNET_H
#define	BEERBUDDYETHERNET_H

#include "../../hardware/arduino/cores/arduino/Arduino.h"

#include "../SPI/SPI.h"
#include "../Ethernet/Ethernet.h"

class BeerBuddyEthernet
{
public:
    uint8_t* macAddress;
    IPAddress serverIp;
    char* serverName;
    long startTime;
    long keepAliveInterval;
    
    BeerBuddyEthernet(byte* mac, IPAddress ip, char* name);
    virtual ~BeerBuddyEthernet();
    void initialize();
    void enableKeepAlive();
    void keepAlive();
    void setOnline();
    void sendRFID(char rfid[]);
private:
    char buffer[200];
    char requestStream[200];
    char* response;
    char* url;
    int y;
    unsigned int bufferLength;
    
    char* createUrl(char path[]);
    char* sendRequest(char url[]);
};

#endif	/* BEERBUDDYETHERNET_H */

