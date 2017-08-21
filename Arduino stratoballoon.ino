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
#include "gyroAccess.h"
#include "ds18b20Access.h"

#pragma region Global var
BME280Access bme;
rtcAccess rtc;
sdAccess sda;
lcdAccess lcd;
ledAccess led;
gpsAccess gps;
gyroAccess gyro;
ds18b20Access ds18b20;

DateTime now;
static unsigned long previousMillis = 0;
static unsigned long previousMillisGPS = 0;
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
	Serial.print(APPNAME);
	Serial.print(" v");
	Serial.println(APPVERSION);
#endif

	//for (int i = 0; i < NB_IO_OUTPUT; i++) // For LowPower
	//	pinMode(LED_PIN, OUTPUT);

	// Init component
	SPI.begin();
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. 

	ds18b20.begin();
	//gyro.begin();
	//gps.begin();
	//rtc.init();
	//bme.init();
	//lcd.begin();
	//lcd.displayText();

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
	int16_t ax, ay, az, gx, gy, gz;
	float altitude, speed, course;
	long prec;
	float dstemp,temp, hum, pres, dewpoint, dhttemp, dhthum;

	//Get time
	previousMillis = millis();

	ds18b20.getData(&dstemp);
	Serial.println(dstemp);
	/*
	if (gps.getData()) {
		gps.getPosition(&lat, &lon, &age);
		gps.getStatistics(&chars, &sentences, &failed_checksum);
		gps.getDateTime(&now);
		gps.getAltitude(&altitude);
		gps.getCourse(&course);
		gps.getSpeed(&speed);
	}*/
	//gyro.getData(&ax, &ay, &az, &gx, &gy, &gz);

	//bme.getData(&temp, &hum, &pres);
	//bme.CalculatedData(&altitude, &dewpoint);

	
	//lcd.displayData(temp, hum, dhttemp, dhthum);

	//Save data
	if (millis() - previousMillis >= LOG_FREQUENCY) {
		previousMillis = millis();
		now = rtc.getDateTime();
		//sda.WriteData(temp, hum, pres, altitude, dewpoint, dhttemp, dhthum, now);
	}
	//led.BlinkLed(1, BLINK_TIME);
	delay(ACQ_FREQUENCY);
}