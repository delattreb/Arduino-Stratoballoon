//
// Created by Bruno on 30/06/2017.
//

class sdAccess {

private:

public:

	sdAccess() {
	}

	~sdAccess() {
	}

	void WriteData(long lat, long lon, float gpsaltitude, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, float dstemp, float temp, float hum, float pres, String now) {
		String strFile = LOG_FILE;
#ifdef DEBUG
		Serial.print("SD W");
		Serial.println(strFile);
#endif		
		if (!SD.begin(SD_PIN)) {}
		File myFile = SD.open(strFile, FILE_WRITE);
		if (myFile) {
			//Date
			myFile.print(now);
			myFile.print(";");

			//GPS
			myFile.print(lat);
			myFile.print(";");
			myFile.print(String(lon));
			myFile.print(";");
			myFile.print(String(gpsaltitude));
			myFile.print(";");

			//Gyro
			myFile.print(String(ax));
			myFile.print(";");
			myFile.print(String(ay));
			myFile.print(";");
			myFile.print(String(az));
			myFile.print(";");
			myFile.print(String(gx));
			myFile.print(";");
			myFile.print(String(gy));
			myFile.print(";");
			myFile.print(String(gz));
			myFile.print(";");

			//DS18B20
			myFile.print(String(dstemp));
			myFile.print(";");

			//BME280
			myFile.print(String(temp));
			myFile.print(";");
			myFile.print(String(hum));
			myFile.print(";");
			myFile.print(String(pres));
			myFile.println(";");

			myFile.close();
		} else {
#ifdef DEBUG
			Serial.println("SD KO");
#endif		
		}
	}

};



