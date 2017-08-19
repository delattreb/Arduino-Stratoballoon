//
// Created by Bruno on 30/06/2017.
//

//Software Version
#define APPNAME "Stratoballoon"
#define APPVERSION "1.5"

//Arduino I/O
#define NB_IO_OUTPUT 8

//SoftwareSerial
#define RXPIN 6
#define TXPIN 5

//DHT22
#define PINDHT22 2

//LCD
#define LCD_ADDR 0x3F
#define LCD_LINE 2
#define LCD_ROW 16

//Acquisition frequency
#define ACQ_FREQUENCY 10000
#define LOG_FREQUENCY 120000
#define ACQ_GPS_DURATION 800

#define BLINK_TIME 50
#define BLINK_INIT 3
#define BLINK_INIT_TIME 250

//MPU6050
#define INTERRUPT_PIN 2  

//LED
#define LED_PIN 7

//SD Access Pin
#define SD_PIN 10

//Serial
#define SERIAL_BAUD 38400 //Check value for 8Mhz

//VAR DIALOG
#define OK 0
#define NOK -1
#define READY 1

//DEBUG MODE
#define DEBUG

//INFO MODE
#define INFO
