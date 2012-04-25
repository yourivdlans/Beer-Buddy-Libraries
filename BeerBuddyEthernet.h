/* 
 * File:   BeerBuddyEthernet.h
 * Author: Pim Vogels, Daan van der Zalm, Joshua Jansen, Youri van der Lans
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
    IPAddress localIp;
    char* serverName;
    long startTime;
    long keepAliveInterval;
    
    BeerBuddyEthernet(byte* mac, IPAddress remote_ip, char* name);
    virtual ~BeerBuddyEthernet();
    void setLocalIp(IPAddress local_ip);
    void initialize();
    void enableKeepAlive();
    void keepAlive();
    void setOnline();
    char* sendRFID(char rfid[12]);
private:
    char buffer[200];
    char requestStream[200];
    char* response;
    char* result;
    char* url;
    int i;
    int y;
    unsigned int bufferLength;
    bool readStream;
    
    char* createUrl(char path[]);
    char* sendRequest(char url[]);
};

#endif	/* BEERBUDDYETHERNET_H */

