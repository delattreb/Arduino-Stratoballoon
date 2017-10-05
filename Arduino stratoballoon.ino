//
// Created by Bruno on 17/08/2017.
//

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "var.h"
#include "libSD.h"
#include "libDS1307.h"
#include "libLED.h"

#ifdef ARDUINO_1
#include "libBME280.h"
#include "libGPS.h"
#include "lib18b20.h"
#include "libSI7021.h"
//#include "libAPRS.h"
#endif 

#ifdef ARDUINO_2
#include "libMPU6050.h"
#endif

#pragma region Global var
libSD sda;
libDS1307 rtc;
libLED led;

#ifdef ARDUINO_1
libBME280 bme;
libGPS gps;
lib18b20 ds18b20;
libSI7021 si7021;
//APRSAccess aprs;
#endif 

#ifdef ARDUINO_2
libMPU6050 gyro;
#endif 
#pragma endregion 

int cpt = 0;

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

#ifdef ARDUINO_1
	ds18b20.begin();
	gps.begin();
	bme.init();
	si7021.init();
	rtc.init();
	//aprs.init();
#endif

#ifdef ARDUINO_2
	gyro.begin();
#endif

	sda.init();
	led.BlinkLed(LED_BLINK_INIT, LED_BLINK_INIT_TIME);
}

//
//  Loop
//
void loop()
{
	long lat, lon;
	unsigned long age;
	int16_t ax, ay, az, gx, gy, gz;
	float gpsaltitude, dstemp, temp, hum, pres, sitemp, sihum, dewpoint, gpsalt, speed, gpscourse;
	String file;


	//TODO Button Start & stop

#ifdef ARDUINO_1
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
	bme.getData(&temp, &hum, &pres);

	// ACQ DS18B20
	ds18b20.getData(&dstemp);

	// Acq SI7021
	sitemp = si7021.getTemperature();
	sihum = si7021.getHumidity();
#endif 

#ifdef ARDUINO_2
	// ACQ Gyro
	gyro.getData(&ax, &ay, &az, &gx, &gy, &gz);
#endif 

	DateTime now = rtc.getDateTime();
	// Save data
	file = LOG_FILE_DATA + String(now.hour()) + ".csv";
	if (cpt < 1000)
		sda.WriteData(lat, lon, gpsalt, gpscourse, speed, ax, ay, az, gx, gy, gz, dstemp, temp, hum, pres, rtc.getDateTimeStrEn(), file);

#ifdef ARDUINO_1
	delay(ACQ_FREQUENCY_1);
#endif

#ifdef ARDUINO_2
	delay(ACQ_FREQUENCY_2);
#endif
	cpt += 1;
}