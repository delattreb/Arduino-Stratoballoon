//
// Created by Bruno on 17/08/2017.
//

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "var.h"
//#include "libBME280.h"
#include "libGPS.h"
#include "libMPU6050.h"
#include "libDS1307.h"
#include "lib18b20.h"
#include "libLED.h"
#include "libSD.h"
#include "libSI7021.h"
//#include "libAPRS.h"


#pragma region Global var
//libBME280 bme;
libGPS gps;
libMPU6050 gyro;
lib18b20 ds18b20;
libDS1307 rtc;
libSD sda;
libLED led;
libSI7021 si7021;
//APRSAccess aprs;
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
	//Init Pin for LED
	pinMode(LED_PIN, OUTPUT);

	// Init component
	SPI.begin();
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. 

	sda.init();
	ds18b20.begin();
	gyro.begin();
	gps.begin(); 
	//bme.init();
	si7021.init();
	rtc.init();
	led.BlinkLed(LED_BLINK_INIT, LED_BLINK_INIT_TIME);
	//aprs.init();
}

//
//  Loop
//
void loop() {
	long lat, lon;
	unsigned long age;
	int16_t ax, ay, az, gx, gy, gz;
	float gpsaltitude, dstemp, temp, hum, pres, sitemp, sihum, dewpoint, gpsalt, speed, gpscourse;

	Serial.println("Start");
	//aprs.locationUpdateExample();
	//aprs.test();

	// ACQ GPS
	
	if (gps.getData()) {
		gps.getPosition(&lat, &lon, &age);
		gps.getAltitude(&gpsalt);
		gps.getCourse(&gpscourse);
		gps.getSpeed(&speed);
	}

	// ACQ BME208
	//bme.getData(&temp, &hum, &pres);

	// ACQ Gyro
	gyro.getData(&ax, &ay, &az, &gx, &gy, &gz);

	// ACQ DS18B20
	ds18b20.getData(&dstemp);

	// Acq SI7021
	sitemp = si7021.getTemperature();
	sihum = si7021.getHumidity();

	// Save data
	sda.WriteData(lat, lon, gpsalt, gpscourse, speed, ax, ay, az, gx, gy, gz, dstemp, temp, hum, pres, rtc.getDateTimeStrEn());

	delay(ACQ_FREQUENCY);
}