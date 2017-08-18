//
// Created by Bruno on 17/08/2017.
//

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#include "var.h"
#include "bme280Access.h"
#include "rtcAccess.h"
#include "sdAccess.h"
#include "lcdAccess.h"
#include "ledAccess.h"
#include "gpsAccess.h"

#pragma region Global var
BME280Access bme;
rtcAccess rtc;
sdAccess sda;
lcdAccess lcd;
ledAccess led;
gpsAccess gps;


String datestr, timestr;
DateTime now;
static unsigned long previousMillis = 0;
unsigned long currentMillis;
#pragma endregion 


//
// Setup
//
void setup() {
#ifdef DEBUG
	Serial.begin(SERIAL_BAUD);
	while (!Serial) {
		;
	}
#endif
	//for (int i = 0; i < NB_IO_OUTPUT; i++) // For LowPower
	//	pinMode(LED_PIN, OUTPUT);

	// Init component
	SPI.begin();
	Wire.begin();

	gps.begin();
	//rtc.init();
	//bme.init();
	//lcd.begin();
	//lcd.displayText();

#ifdef DEBUG
	Serial.print(APPNAME);
	Serial.print(" v");
	Serial.println(APPVERSION);
#endif
	led.BlinkLed(BLINK_INIT, BLINK_INIT_TIME);
}

//
//  Loop
//
void loop() {
	long lat, lon;
	unsigned long age;

	unsigned long chars;
	unsigned short sentences;
	unsigned short failed_checksum;

	DateTime now;


	float altitude, speed, course;

	long prec;
	float temp, hum, pres, dewpoint, dhttemp, dhthum;

	gps.getPosition(&lat, &lon, &age);
	//gps.getStatistics(&chars, &sentences, &failed_checksum);
	//gps.getDateTime(&now);
	//gps.getAltitude(&altitude);
	gps.getCourse(&course);
	gps.getSpeed(&speed);

	currentMillis = millis();

	//bme.getData(&temp, &hum, &pres);
	//bme.CalculatedData(&altitude, &dewpoint);

	//led.BlinkLed(1, BLINK_TIME);
	//lcd.displayData(temp, hum, dhttemp, dhthum);

	/* Réalise une prise de mesure toutes les DELAY_BETWEEN_MEASURES millisecondes */
	if (currentMillis - previousMillis >= LOG_FREQUENCY) {
		previousMillis = currentMillis;
		now = rtc.getDateTime();
		//sda.WriteData(temp, hum, pres, altitude, dewpoint, dhttemp, dhthum, now);
	}
	//delay(ACQ_FREQUENCY);
}