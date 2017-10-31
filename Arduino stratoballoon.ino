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
#include "libGPS.h"
#include "lib18b20.h"
#include "libSI7021.h"
#include "libAPRS.h"
#endif 

#ifdef ARDUINO_2
#include "libMPU6050.h"
#include "libBME280.h"
#endif

#pragma region Global var
long lat, lon;
unsigned long age;
int16_t ax, ay, az, gx, gy, gz;
float gpsaltitude, dstemp, temp, hum, pres, sitemp, sihum, dewpoint, gpsalt, speed, gpscourse;
String file;
bool bstart = false, bstop = false;

libSD sda;
libDS1307 rtc;
libLED led;

#ifdef ARDUINO_1
libGPS gps;
lib18b20 ds18b20;
libSI7021 si7021;
APRSAccess aprs;
#endif 

#ifdef ARDUINO_2
libBME280 bme;
libMPU6050 gyro;
#endif 
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
	//Button
	pinMode(PIN_START, INPUT);
	pinMode(PIN_STOP, INPUT);

	//Init Pin for LED
	pinMode(LED_PIN, OUTPUT);

	// Init component
	SPI.begin();
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. 
	rtc.init();
	sda.init();
	led.BlinkLed(LED_BLINK_INIT, LED_BLINK_TIME);

#ifdef ARDUINO_1
	ds18b20.begin();
	gps.begin();
	si7021.init();
	//aprs.init();
#endif

#ifdef ARDUINO_2
	bme.init();
	gyro.begin();
#endif
}

//
//  Loop
//
void loop()
{
	// Read button
	if (digitalRead(PIN_START) == HIGH) {
		bstart = true;
		bstop = false;
		led.BlinkLed(LED_BLINK_START, LED_BLINK_TIME);
	}
	if (digitalRead(PIN_STOP) == HIGH) {
		bstop = true;
		bstart = false;
		led.BlinkLed(LED_BLINK_STOP, LED_BLINK_TIME);
	}

	if (bstart && !bstop) {
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

		// ACQ DS18B20
		ds18b20.getData(&dstemp);

		// Acq SI7021
		sitemp = si7021.getTemperature();
		sihum = si7021.getHumidity();
#endif 

#ifdef ARDUINO_2
		// ACQ BME280
		bme.getData(&temp, &hum, &pres);

		// ACQ Gyro
		gyro.getData(&ax, &ay, &az, &gx, &gy, &gz);
#endif 

		DateTime now = rtc.getDateTime();
		// Save data
		file = LOG_FILE_DATA + String(now.hour()) + ".csv";
		sda.WriteData(lat, lon, gpsalt, gpscourse, speed, ax, ay, az, gx, gy, gz, dstemp, temp, hum, pres, rtc.getDateTimeStrEn(), file);

#ifdef ARDUINO_1
		delay(ACQ_FREQUENCY_1);
#endif

#ifdef ARDUINO_2
		delay(ACQ_FREQUENCY_2);
#endif
	}
}