/*
 * Arduino-powered irrigation system.
 *
 * Checks soil moisture level and irrigates at set times when needed.
 *
 * Danilo Riffo, 2018
 * danriffo@gmail.com
 *
 *
 *
 *
 *******************************************************************************
 * Pins used:
 *
 *  0   1   2   3   4   5   6   7         8   9  10   11   12  13
 *            |RST IO  CLK GND VCC|      HY  PMP|CS  MOSI MISO SCK|
 *            |        RTC        |             |     microSD     |
 *
 *
 * A0  A1  A2  A3  A4  A5
 * HY  TH1 TH2 THO
 *
 *
 *
 */

#include <Streaming.h>
#include <DS1302RTC.h>	//for RTC support
#include <Time.h>		//for RTC support
#include <SPI.h>		//for SD card support
#include <SD.h>			//for SD card support

/*
 * Irrigation settings.
 *
 * Edit when necessary
 *
 */
long pumpTime=90000;	//time in ms for the pump to continuously work when needed. 2L/min output. Works 2 times each set hour.
int pumpThresh=60;	//soil moisture threshold to activate the pump.
int pumpHour1=5;	//RTC time (hour, 24h format) to activate the pump if needed
int pumpHour2=19;   //same as pumpHour1. Added as second check
int deepD1=7;		//day to deeply wet the ground
int deepD2=14;		//same as above
int deepD3=21;		//same as above
int deepD4=28;		//same as above
int deepH=22;		//hour to deeply irrigate


//set RTC pins and create global object
DS1302RTC RTC( 3, 4, 5 ); //CE/RST, IO, CLK
// Required to set the time
#define DS1302_GND_PIN 6
#define DS1302_VCC_PIN 7
bool rtcFlag = 1; 	//1=ok, 0=nope

// File to store data
char dataFile[] = "data.txt";

//hygrometer pin setting
#define hygroPin A0
#define hygroPinOn 8	//used to turn on/off the sensor via transistor
int hygroValue;

//pump pin setting
#define pumpPin 9

//global flag for watering type performed
char watered;	//y,n,d (yes, no, deep)

//defines thermistor pin and extra resistor load (in ohms)
#define thermistorPin1 A1
#define thermistorPin2 A2
#define thermistorPinOn A3	//on/off switch for thermistor
#define thermistorLoad1 7000 //9900	//says my multimeter
#define thermistorLoad2 7000 //9700
#define thermistorSamples 5  //samples to average for increased accuracy
#define thermistor25C 10000
#define thermistorBeta 3343.25
float temp1;
float temp2;

//define global variable to store the current hour
int hora=14;


void setup(){
  analogReference(EXTERNAL);	//increase analog accuracy
  Serial.begin(9600);

  digitalWrite ( 13, LOW ); 			//disable RX LED
  digitalWrite ( hygroPinOn, LOW );  	//disable hygrometer until needed
  pinMode ( thermistorPinOn, OUTPUT );
  digitalWrite ( thermistorPinOn, LOW );//disable thermistor until needed



  testRTC();	//tests and initializes the RTC
  //setRTC();		//manually set RTC when needed
  hora = hour(RTC.get()); //initialize

  pinMode ( pumpPin, OUTPUT );
  digitalWrite ( pumpPin, LOW );

  // initialize microSD module
  if (!SD.begin(10)) {	//use pin 10 as ChipSelect. This is the default.
	  Serial.println("uSD initialization failed!. Status will not be recorded.");
  }
  else {
	  //readConfig(); //we know card is accessible.
	  Serial.println("uSD initialization done.");
  }

}

void loop(){
	int Hora = hour(RTC.get());

	if ( Hora > hora || ( Hora == 0 && hora > 0 ) ){	//runs only once an hour
		hora = Hora;	//set actual hour
		// disable all except temperature
		//checkHygro();
		watered = 'n';
		/*if ( Hora == pumpHour1 || Hora == pumpHour2 ){
			startPump(pumpTime);
			//delay(300000);
			//startPump(pumpTime);
		}/*else if ( Hora == deepH){
			int Day = day(RTC.get());
			if ( Day == deepD1 || Day == deepD2 || Day == deepD3 || Day == deepD4 ){
				//ignore soil moisture level and just deeply wet the soil
				Serial<< F("deeply watering as scheduled...") << endl;
				deepWatering();
			}
		}*/ //commented out to disable deep irrigation

		getTemperature();

		dataWrite();
	}
    delay(9000); //sleeps for 9s. Enough to keep a powerbank alive
    sdDummyRead(); //then read from microSD to waste some juice
}

/************************************************************
 * Dummy read from uSD card.
 * Used o keep Powerbank alive.
 *
 */
void sdDummyRead(){
	File file = SD.open(dataFile);
	char single;

	if (!file){	//if error, then error :P
		Serial << F("error opening file <") << dataFile << F(">") << endl;
	}else{
		single=file.read(); //do NOTHING with this read char
	}

	file.close();	//close the file
}


/************************************************************
 * Read configuration from uSD card.
 *
 */
void readConfig(){
	File file = SD.open("config.cfg");	//open the file
	char single;

	if (!file){	//if error, then error :P
		Serial << F("error opening file <config.cfg>") << endl;
	}else{

		while (file.available()){
			single=file.read(); //do something with this read char
		}

	}

	file.close();	//close the file
}


/************************************************************
 * Begin RTC (Real Time Clock) control.
 *
 */
void testRTC(){
	//test if the DS1302 module is working

	//setSyncProvider() causes the Time library to synchronize with the
	//external RTC by calling RTC.get() every five minutes by default.
	setSyncProvider(RTC.get);

	Serial.println("DS1302RTC Read Test");
	Serial.println("-------------------");

	// Activate RTC module
	digitalWrite(DS1302_GND_PIN, LOW);
	pinMode(DS1302_GND_PIN, OUTPUT);

	digitalWrite(DS1302_VCC_PIN, HIGH);
	pinMode(DS1302_VCC_PIN, OUTPUT);

	Serial.println("RTC module activated");
	Serial.println();
	delay(500);

	if (RTC.haltRTC()) {
		Serial.println("The DS1302 is stopped.");
		Serial.println();
	}
	if (!RTC.writeEN()) {
		Serial.println("The DS1302 is write protected. This is normal.");
		Serial.println();
	}

	delay(5000);

	time_t t = RTC.get();
	if ( year(t) < 2018 ){ 	//assume date is wrong
		Serial << F("Wrong time. Resetting module.") << endl;
		setRTC();
	}
	else{
		Serial << F("Module working properly.") << endl;
		printDate(t);
	}

	Serial.println("DS1302RTC Test End");
	Serial.println("-------------------");
}

void setRTC(){		//initializes DS1302 module.

	static time_t tLast;
    time_t t;
    tmElements_t tm;
    uint8_t count=0;

	while ( timeStatus() != timeSet && count < 11 ){		//if time is not set for the module, set it

		Serial << F("waiting for date at serial input...") << endl;
		count++;
		delay(5000);

		//check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
		if (Serial.available() >= 12) {
			//note that the tmElements_t Year member is an offset from 1970,
			//but the RTC wants the last two digits of the calendar year.
			//use the convenience macros from Time.h to do the conversions.
			int y = Serial.parseInt();
			if (y >= 100 && y < 1000)
				Serial << F("Error: Year must be two or four digits") << endl;
			else {
				if (y >= 1000)
					tm.Year = CalendarYrToTm(y);
				else    //(y < 100)
					tm.Year = y2kYearToTm(y);
				tm.Month = Serial.parseInt();
				tm.Day = Serial.parseInt();
				tm.Hour = Serial.parseInt();
				tm.Minute = Serial.parseInt();
				tm.Second = Serial.parseInt();
				t = makeTime(tm);
				//use the time_t value to ensure correct weekday is set
				if(RTC.set(t) == 0) { // Success
					setTime(t);
					Serial << F("RTC set to: ");
					printDate(t);
				}
				else
					Serial << F("RTC set failed") << endl;
				//dump any extraneous input
				while (Serial.available() > 0) Serial.read();
			}
		}

		t = RTC.get(); //now();
		if (t != tLast) {
			tLast = t;
			printDate(t);
		}

		if ( count == 10 )
			Serial << F("last try.") << endl;
		else if ( count == 11 ){
			Serial << F("RTC set failed.") << endl;
			rtcFlag = 0;
		}

    }
}

//Print an integer in "00" format (with leading zero),
//followed by a delimiter character to Serial.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim){
    if (val < 10) Serial << '0';
    Serial << _DEC(val);
    if (delim > 0) Serial << delim;
    return;
}

void printDate(time_t t){	//self-explanatory
	printI00(day(t), 0);
	Serial << monthShortStr(month(t)) << _DEC(year(t));
	Serial << ' ';
	printI00(hour(t), ':');
	printI00(minute(t), ':');
	printI00(second(t), ' ');
	Serial << endl;
}

/*
 * End RTC (Real Time Clock) control.
 *
 ************************************************************/



/************************************************************
 * Begin Hygrometer control.
 *
 */

void checkHygro(){		//ask hygrometer "sup bruh?"
    hygroValue = 0;

    digitalWrite ( 8, HIGH ); //enable hygrometer
    delay(10000); //keep the sensor working for 10s to ensure accuracy

    hygroValue = map(analogRead(hygroPin),550,0,0,100);
    Serial << F("Moisture: ") << hygroValue << F("%") << endl;

    digitalWrite ( 8, LOW ); //disable hygrometer again.
}

/*
 * End Hygrometer control.
 *
 ************************************************************/



/************************************************************
 * Begin Pump control.
 *
 */

void startPump(long time){

	if ( hygroValue <= pumpThresh ){
		Serial << F("watering the plants...");
		digitalWrite ( pumpPin, HIGH );
		digitalWrite ( 13, HIGH ); //enable RX LED
		delay(time);
		digitalWrite ( pumpPin, LOW );
		digitalWrite ( 13, LOW ); //disable RX LED

		Serial << F("     Finished.") << endl;
		watered = 'y';
	}
}


void deepWatering(){

	for ( int i=0; i<10; i=i+1 ){ //over 2.5 hours, 10 times. Total 5 liters.
		Serial << F("cycle ") << i+1 << F(" of 10.") << endl;
		startPump(16000); //about 0.5liters of water.
		delay( 900000 ); //15 minutes delay to let water infiltrate.
	}
	Serial << F("Deep watering done.") << endl;
	watered = 'd';
}

/*
 * End Pump control.
 *
 ************************************************************/



/************************************************************
 * Begin MicroSD control.
 *
 */

void dataWrite(){	//build and write a data line into the microSD card

	char line[70];
	char buffer[12];

	sprintf(line, "%04i/%02i/%02i %02i:%02i %03i         %c        ", year(RTC.get()),month(RTC.get()),day(RTC.get()),hour(RTC.get()),minute(RTC.get()),hygroValue,watered);
	dtostrf(temp1, 5, 2, buffer);
	strcat(line, buffer);
	dtostrf(temp2, 5, 2, buffer);
	strcat(line, " ");
	strcat(line, buffer);

	Serial << F("Writing report line to microSD card... ");
	int err = dataWriteOnSD(line);
	if (err)
		Serial << F("An error occurred while writing to microSD card.") << endl;
	else
		Serial << F("SDcard write Ok.") << endl;

}

int dataWriteOnSD(char *wDATA){	//write wDATA into wFILE on sdcard

	/* lines should follow this format:
	 *
	 * year/month/day hour:minute HygroValue% watered? ºCinside ºCoutside
	 * int	int	  int int  int	  int         [y,n,d]  00.00    00.00
	 *
	 *
	 * and this spacing:
	 *
	 * year/mm/dd hh:mm HygroValue% watered? ºCin  ºCout
	 *
	 */

	//test if file exists
	File file = SD.open(dataFile, FILE_READ);	//open file in read mode

	if (!file){
		// if file doesn't exist, try creating it with header line
		file = SD.open(dataFile, FILE_WRITE);
		if (!file){	//if error, then error :P
			Serial << F("error opening file <") << dataFile << F(">") << endl;
			return(1);	//errorcode 1
		}
		Serial << F("Data file didn't exist. Created new one.") << endl;
		file.println("year/mm/dd hh:mm HygroValue% watered? ºCin  ºCout");	//write header
		file.close();
	}
	file.close();


	file = SD.open(dataFile, FILE_WRITE);	//open the file
	if (!file){	//if error, then error :P
		Serial << F("error opening file <") << dataFile << F(">") << endl;
		return(1);	//errorcode 1
	}

	file.println(wDATA);	//write line to file

	file.close();	//close the file
	return(0);	//no error

}

/*
 * End MicroSD control.
 *
 ************************************************************/


/************************************************************
 * Begin Thermistor control.
 *
 */

void getTemperature (){
	float average1=0.0;
	float average2=0.0;
	float vOut1=0.0;
	float vOut2=0.0;
	int sample=0;
	float voltage=4.35;	//specific value to my board/transistor configuration

	digitalWrite (thermistorPinOn, HIGH);	//turns the thermistors on
	delay(20000); 	//wait 10s for thermistors to properly measure

	average1 = 0.0;
	average2 = 0.0;
	// take N samples in a row, with a slight delay, and add them up
	for (int i=0; i< thermistorSamples; i++){
		sample = analogRead(thermistorPin1);
		//Serial << F("Thermistor1 reading ") << i << F(": ") << sample << endl;
		average1 += sample;
		sample = analogRead(thermistorPin2);
		//Serial << F("Thermistor2 reading ") << i << F(": ") << sample << endl;
		average2 += sample;
		delay(100);
	}

	//average taken samples
	average1 /= thermistorSamples;
	average2 /= thermistorSamples;
	Serial << F("Average TH1 reading: ") << average1 << endl;
	Serial << F("Average TH2 reading: ") << average2 << endl;

	// convert the value to resistance
	vOut1 = voltage * (float)average1 / 1024.0 ;
	vOut2 = voltage * (float)average2 / 1024.0 ;
	Serial << F("vOut1: ") << vOut1 << endl;
	Serial << F("vOut2: ") << vOut2 << endl;

	vOut1 = thermistorLoad1 * (( voltage / vOut1 ) - 1.0);	//viva la resistance!
	vOut2 = thermistorLoad2 * (( voltage / vOut2 ) - 1.0);
	Serial << F("Thermistor1 resistance: ") << vOut1 << F(" ohms")<< endl;
	Serial << F("Thermistor2 resistance: ") << vOut2 << F(" ohms")<< endl;

	//Convert resistance to ºC
	temp1 = vOut1 / thermistor25C;  	// (R/Ro)
	temp1 = log(temp1);                 // ln(R/Ro)
	temp1 /= thermistorBeta;            // 1/B * ln(R/Ro)
	temp1 += 1.0 / (25 + 273.15); 		// + (1/To)
	temp1 = 1.0 / temp1;                // Invert
	temp1 -= 273.15;                    // convert ºK to ºC

	temp2 = vOut2 / thermistor25C;  	// (R/Ro)
	temp2 = log(temp2);                 // ln(R/Ro)
	temp2 /= thermistorBeta;            // 1/B * ln(R/Ro)
	temp2 += 1.0 / (25 + 273.15); 		// + (1/To)
	temp2 = 1.0 / temp2;                // Invert
	temp2 -= 273.15;                    // convert ºK to ºC

	Serial << F("Temperature1: ") << temp1 << F("ºC") << endl;
	Serial << F("Temperature2: ") << temp2 << F("ºC") << endl;

	digitalWrite (thermistorPinOn, LOW);	//Thermistors out.

}
