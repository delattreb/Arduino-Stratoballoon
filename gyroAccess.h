#include "I2Cdev.h"
#include <MPU6050.h>

MPU6050 accelgyro;

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

#ifdef DEBUG
		Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
#endif // DEBUG

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
		//accelgyro.getAcceleration(&ax, &ay, &az);
		//accelgyro.getRotation(&gx, &gy, &gz);
	}
};

