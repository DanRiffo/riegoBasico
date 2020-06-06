#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-06-05 21:40:41

#include "Arduino.h"
#include <Streaming.h>
#include <DS1302RTC.h>
#include <Time.h>
#include <SPI.h>
#include <SD.h>

void setup();
void loop();
void sdDummyRead();
void readConfig();
void testRTC();
void setRTC();
void printI00(int val, char delim);
void printDate(time_t t);
void checkHygro();
void startPump(long time);
void deepWatering();
void dataWrite();
int dataWriteOnSD(char *wDATA);
void getTemperature ();

#include "riegoBasico.ino"


#endif
