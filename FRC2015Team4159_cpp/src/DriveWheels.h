#include "WPILib.h"

#ifndef FRC2015TEAM4159_DRIVEWHEELS_H_
#define FRC2015TEAM4159_DRIVEWHEELS_H_

class DriveWheels {
public:
	Victor *frontLeftMotor;
	Victor *rearLeftMotor;
	Victor *frontRightMotor;
	Victor *rearRightMotor;

	DriveWheels(Victor *frontLeft, Victor *rearLeft, Victor *frontRight, Victor *rearRight);
	DriveWheels(int channel1, int channel2, int channel3, int channel4);
	~DriveWheels(void);

	void stopAll(void);
};

#endif
