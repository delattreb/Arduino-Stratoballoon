//
// Created by Bruno on 30/06/2017.
//

//Software Version
#define APPNAME "Stratoballoon"
#define APPVERSION "1.8"

//SoftwareSerial
#define RXPIN 6
#define TXPIN 5

//Acquisition frequency
#define ACQ_FREQUENCY 10000
#define LOG_FREQUENCY 20000
#define ACQ_GPS_DURATION 800

#define BLINK_TIME 50
#define BLINK_INIT 3
#define BLINK_INIT_TIME 250

//MPU6050
#define INTERRUPT_PIN 2  

//DS18B20
#define ONE_WIRE_BUS 8

//LED
#define LED_PIN 7

//SD Access Pin
#define SD_PIN 10
#define LOG_FILE "acq.log"

//Serial
#define SERIAL_BAUD 38400 //Check value for 8Mhz
#define SERIAL_SOFT 9600

//VAR DIALOG
#define OK 0
#define NOK -1
#define READY 1

//DEBUG MODE
#define DEBUG

//INFO MODE
//#define INFO
