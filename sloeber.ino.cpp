#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-05-28 15:49:48

#include "Arduino.h"
#include <Streaming.h>
#include <DS1302RTC.h>
#include <Time.h>
#include <SPI.h>
#include <SD.h>

void setup();
void loop();
void readConfig();
void testRTC();
void setRTC();
void printI00(int val, char delim);
void printDate(time_t t);
void checkHygro();
void startPump(long time);
void deepWatering();
void dataWrite();
int dataWriteOnSD(char *wDATA, char *wFILE);
void getTemperature ();

#include "riegoBasico.ino"


#endif
