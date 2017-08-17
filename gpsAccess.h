//
// Created by Bruno on 17/08/2017.
//

#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS tinyGPS;
SoftwareSerial ss(RX_PIN, TX_PIN);

class gpsAccess {

private:


public:

	gpsAccess() {
	}

	~gpsAccess() {
	}


	//
	// getDateTime
	//
	DateTime getDateTime()
	{
		int year;
		unsigned long age;
		byte month, day, hour, minute, second, hundredths;
		DateTime gpsNow;
		tinyGPS.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);

		gpsNow.setyear(year);
		gpsNow.setmonth(month);
		gpsNow.setday(day);

		gpsNow.sethour(hour);
		gpsNow.setminute(minute);
		gpsNow.setsecond(second);

		return gpsNow;
	}

	//
	// getPosition
	//
	void getPosition(float* lat, float* lon, unsigned long* age)
	{
		bool newData = false;

		while (ss.available())
		{
			char c = ss.read();
			// Serial.write(c); // uncomment this line if you want to see the GPS data flowing
			if (tinyGPS.encode(c))
				newData = true;
		}

		if (newData) {
			tinyGPS.f_get_position(lat, lon, age);

#ifdef DEBUG
			float flat, flon;
			unsigned long fage;
			flat = *lat;
			flon = *lon;
			fage = *age;

			Serial.print("Latitude: ");
			Serial.println(flat, 6);
			Serial.print("Longitude: ");
			Serial.println(flon);
			Serial.print("Age: ");
			Serial.println(fage);
#endif // DEBUG
		}
		else {
#ifdef DEBUG
			Serial.println("No GPS Data");
#endif
		}
	}

	//
	// getSpeed
	//
	void getSpeed(float* speed)
	{
		*speed = tinyGPS.f_speed_kmph();
	}

	//
	// getPrecision
	//
	void getPrecision(long* speed)
	{
		*speed = tinyGPS.hdop();
	}
};
