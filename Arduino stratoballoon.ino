//
// Created by Bruno on 17/08/2017.
//

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#include "var.h"
#include "bme280Access.h"
#include "sdAccess.h"
#include "gpsAccess.h"
#include "gyroAccess.h"
#include "rtcAccess.h"
#include "ds18b20Access.h"

#pragma region Global var
BME280Access bme;
sdAccess sda;
gpsAccess gps;
gyroAccess gyro;
ds18b20Access ds18b20;
rtcAccess rtc;
static unsigned long previousMillis = 0;
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
	// Init component
	SPI.begin();
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. 

	ds18b20.begin();
	gyro.begin();
	gps.begin();
	bme.init();
	rtc.init();

	//Get time
	previousMillis = millis();
}

//
//  Loop
//
void loop() {
	long lat, lon;
	unsigned long age;
	int16_t ax, ay, az, gx, gy, gz;
	float gpsaltitude, dstemp, temp, hum, pres, dewpoint, altitude, speed, course;

	//DateTime now;

	// ACQ GPS
	if (gps.getData()) {
		gps.getPosition(&lat, &lon, &age);
		gps.getAltitude(&gpsaltitude);
		//gps.getCourse(&course);
		//gps.getSpeed(&speed);
	}

	// ACQ Gyro
	gyro.getData(&ax, &ay, &az, &gx, &gy, &gz);

	// ACQ DS18B20
	ds18b20.getData(&dstemp);

	// ACQ BME208
	bme.getData(&temp, &hum, &pres);

	//Save data on SD card
	if (millis() - previousMillis >= LOG_FREQUENCY) {
		previousMillis = millis();
		sda.WriteData(lat, lon, gpsaltitude, ax, ay, az, gx, gy, gz, dstemp, temp, hum, pres, rtc.getDateTimeStr());
	}
	delay(ACQ_FREQUENCY);
}