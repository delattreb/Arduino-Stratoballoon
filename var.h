//
// Created by Bruno on 30/06/2017.
//

//Software Version
#define APPNAME "Stratoballoon"
#define APPVERSION "2.3"

// Arduino
//#define ARDUINO_1
#define ARDUINO_2

#define DEBUG
#define INFO

// BUTTON
#define PIN_START 2
#define PIN_STOP 3

//SoftwareSerial
#define RXPIN 6
#define TXPIN 5

//SoftwareSerial -> Arduino 3
#define RXPIN 7
#define TXPIN 8

//Arduino N°3
//RX1 Pin 2 RX2 Pin 3
//TX1 4 TX2 Pin 5

//Acquisition frequency
#define ACQ_FREQUENCY_1 10000
#define ACQ_FREQUENCY_2 2000
#define ACQ_GPS_DURATION 800

//DS18B20
#define ONE_WIRE_BUS 4

//LED
#define LED_PIN 9
#define LED_BLINK_TIME 50
#define LED_BLINK_INIT 10
#define LED_BLINK_START 5
#define LED_BLINK_STOP 2
#define LED_BLINK_TIME 100


//SD Access Pin
#define SD_CS_PIN SS //Pin N°10
#define LOG_FILE_DATA "log"

//Serial
#define SERIAL_BAUD 9600 //Check value for 8Mhz
#define SERIAL_SOFT 9600

//VAR DIALOG
#define OK 0
#define NOK -1
#define READY 1