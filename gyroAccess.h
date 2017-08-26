#include "I2Cdev.h"
#include <MPU6050.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

//MPU6050 accelgyro;     // <-- use for AD0 low
MPU6050 accelgyro(0x69); // <-- use for AD0 high

class gyroAccess {

private:

public:

	gyroAccess() {
	}

	~gyroAccess() {
	}

	void begin() {
		// initialize device
		accelgyro.initialize();

#ifdef INFO
		Serial.println(accelgyro.testConnection() ? "MPU6050 OK" : "MPU6050 KO!");
#endif 

		/*// use the code below to change accel/gyro offset values
		accelgyro.setXGyroOffset(0);
		accelgyro.setYGyroOffset(0);
		accelgyro.setZGyroOffset(0);
		accelgyro.setXAccelOffset(0);
		accelgyro.setYAccelOffset(0);
		accelgyro.setZAccelOffset(0);
		*/
	}

	void getData(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz) {
		accelgyro.getMotion6(ax, ay, az, gx, gy, gz);
#ifdef INFO
		Serial.print("Ax: ");
		Serial.print(*ax);
		Serial.print(" Ay: ");
		Serial.print(*ay);
		Serial.print(" Az: ");
		Serial.print(*az);
		Serial.print(" Gx: ");
		Serial.print(*gx);
		Serial.print(" Gy: ");
		Serial.print(*gy);
		Serial.print(" Gz: ");
		Serial.println(*gz);
#endif 
		//accelgyro.getAcceleration(&ax, &ay, &az);
		//accelgyro.getRotation(&gx, &gy, &gz);
	}
};

