#include "TinyGPS.h"
#include <SoftwareSerial.h>


TinyGPS gps;
#define RXPIN 3
#define TXPIN 2
SoftwareSerial nss(RXPIN, TXPIN);


void setup()
{
  Serial.begin(9600);
  nss.begin(9600);
}

void loop()
{
  while (nss.available())
  {
    int c = nss.read();
    if (gps.encode(c))
    {
      long lat, lon;
      unsigned long fix_age, time, date, speed, course;
      unsigned long chars;
      unsigned short sentences, failed_checksum;
 
      // retrieves +/- lat/long in 100000ths of a degree
      gps.get_position(&lat, &lon, &fix_age);
           
      Serial.print("lat: ");
      Serial.println(lat);
      Serial.print("lon: ");
      Serial.println(lon);
      
      // time in hhmmsscc, date in ddmmyy
      gps.get_datetime(&date, &time, &fix_age);
 
      // returns speed in 100ths of a knot
      speed = gps.speed();
 
      // course in 100ths of a degree
      course = gps.course();

      // statistics
      gps.stats(&chars, &sentences, &failed_checksum);

      float flat, flon;
 
      // returns +/- latitude/longitude in degrees
      gps.f_get_position(&flat, &flon, &fix_age);
     
      float falt = gps.f_altitude(); // +/- altitude in meters
      float fc = gps.f_course(); // course in degrees
      float fk = gps.f_speed_knots(); // speed in knots
      float fmph = gps.f_speed_mph(); // speed in miles/hr
      float fmps = gps.f_speed_mps(); // speed in m/sec
      float fkmph = gps.f_speed_kmph(); // speed in km/hr

      //DateTime
      int year;
      byte month, day, hour, minute, second, hundredths;
      
      gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &fix_age);

      //Detect Fix
      gps.f_get_position(&flat, &flon, &fix_age);
      if (fix_age == TinyGPS::GPS_INVALID_AGE)
        Serial.println("No fix detected");
      else if (fix_age > 5000)
        Serial.println("Warning: possible stale data!");
      else
        Serial.println("Data is current.");
    }
  }
}
