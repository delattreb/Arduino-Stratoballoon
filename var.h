//
// Created by Bruno on 30/06/2017.
//

//Software Version
#define APPNAME "Stratoballoon"
#define APPVERSION "2.1"

// Arduino
//#define ARDUINO_1
#define ARDUINO_2

#define DEBUG
#define INFO

//SoftwareSerial
#define RXPIN 6
#define TXPIN 5

//Acquisition frequency
#define ACQ_FREQUENCY_1 10000
#define ACQ_FREQUENCY_2 2000
#define ACQ_GPS_DURATION 800

//MPU6050
#define INTERRUPT_PIN 2  

//DS18B20
#define ONE_WIRE_BUS 7

//LED
#define LED_PIN 8
#define LED_BLINK_TIME 50
#define LED_BLINK_INIT 10
#define LED_BLINK_INIT_TIME 100


//SD Access Pin
#define SD_PIN 10
#define LOG_FILE_DATA "log"

//Serial
#define SERIAL_BAUD 9600 //Check value for 8Mhz
#define SERIAL_SOFT 9600

//VAR DIALOG
#define OK 0
#define NOK -1
#define READY 1


