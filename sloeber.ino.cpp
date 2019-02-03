#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2019-02-03 17:05:42

#include "Arduino.h"
#include <Streaming.h>
#include <DS1302RTC.h>
#include <Time.h>
#include <SPI.h>
#include <SD.h>

void setup();
void loop();
void testRTC();
void setRTC();
void printI00(int val, char delim);
void printDate(time_t t);
void checkHygro();
void startPump(long time);
void deepWatering();
void dataWrite();
int dataWriteOnSD(char wDATA[], char wFILE[]);

#include "riegoBasico.ino"


#endif
