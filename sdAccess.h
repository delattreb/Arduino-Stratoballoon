//
// Created by Bruno on 30/06/2017.
//

#include <SD.h>
#include "ledAccess.h"

class sdAccess {

private:
	ledAccess led;
public:

	sdAccess() {
	}

	~sdAccess() {
	}

	void init()
	{
		if (!SD.begin(SD_PIN)) {
#ifdef INFO
			Serial.println("SD KO!");
#endif 
		}
		else {
#ifdef INFO
			Serial.println("SD OK");
#endif 
		}
	}

	void WriteData(long lat, long lon, float gpsaltitude, float gpscourse, float speed, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, float dstemp, float temp, float hum, float pres, String now) {
		if (!SD.begin(SD_PIN)) {}
		File myFile = SD.open(LOG_FILE, FILE_WRITE);
		if (myFile) {
			//Date
			myFile.print(now);
			myFile.print(";");

			//GPS
			myFile.print(lat);
			myFile.print(";");
			myFile.print(lon);
			myFile.print(";");
			myFile.print(String(gpsaltitude));
			myFile.print(";");
			myFile.print(String(gpscourse));
			myFile.print(";");
			myFile.print(String(speed));
			myFile.print(";");

			//Gyro
			myFile.print(ax);
			myFile.print(";");
			myFile.print(ay);
			myFile.print(";");
			myFile.print(az);
			myFile.print(";");
			myFile.print(gx);
			myFile.print(";");
			myFile.print(gy);
			myFile.print(";");
			myFile.print(gz);
			myFile.print(";");

			//DS18B20
			myFile.print(String(dstemp));
			myFile.print(";");

			//BME280
			myFile.print(String(temp));
			myFile.print(";");
			myFile.print(String(hum));
			myFile.print(";");
			myFile.println(String(pres));
			myFile.close();
			led.BlinkLed(1, LED_BLINK_TIME);
		}
		else {
			led.BlinkLed(3, LED_BLINK_TIME);
		}
	}
};



