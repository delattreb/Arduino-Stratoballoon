//
// Created by Bruno on 17/08/2017.
//

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "var.h"
#include "bme280SparkAccess.h"
#include "gpsAccess.h"
#include "gyroAccess.h"
#include "rtcAccess.h"
#include "ds18b20Access.h"
#include "sdAccess.h"

#pragma region Global var
BME280SparkAccess bme;
gpsAccess gps;
gyroAccess gyro;
ds18b20Access ds18b20;
rtcAccess rtc;
sdAccess sda;
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

	sda.init();
	ds18b20.begin();
	gyro.begin();
	gps.begin(); 
	bme.init();
	rtc.init();
}

//
//  Loop
//
void loop() {
	long lat, lon;
	unsigned long age;
	int16_t ax, ay, az, gx, gy, gz;
	float gpsaltitude, dstemp, temp, hum, pres, alt, dewpoint, gpsalt, speed, gpscourse;
	
	// ACQ GPS
	
	if (gps.getData()) {
		gps.getPosition(&lat, &lon, &age);
		gps.getAltitude(&gpsalt);
		gps.getCourse(&gpscourse);
		gps.getSpeed(&speed);
	}

	// ACQ BME208
	bme.getData(&temp, &hum, &pres, &alt);

	// ACQ Gyro
	gyro.getData(&ax, &ay, &az, &gx, &gy, &gz);

	// ACQ DS18B20
	ds18b20.getData(&dstemp);
	
	// Save data on SD card
	sda.WriteData(lat, lon, gpsalt, gpscourse, speed, ax, ay, az, gx, gy, gz, dstemp, temp, hum, pres, rtc.getDateTimeStrEn());

	delay(ACQ_FREQUENCY);
}