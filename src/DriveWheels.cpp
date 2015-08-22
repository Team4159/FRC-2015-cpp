#include "DriveWheels.h"

DriveWheels::DriveWheels(Victor *frontLeft, Victor *rearLeft, Victor *frontRight, Victor *rearRight)
{
	frontLeftMotor = frontLeft;
	rearLeftMotor = rearLeft;
	frontRightMotor = frontRight;
	rearRightMotor = rearRight;
}

DriveWheels::DriveWheels(int channel1, int channel2, int channel3, int channel4)
{
	frontLeftMotor = new Victor(channel1);
	rearLeftMotor = new Victor(channel2);
	frontRightMotor = new Victor(channel3);
	rearRightMotor = new Victor(channel4);
}

DriveWheels::~DriveWheels(void)
{
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
}

void DriveWheels::stopAll(void)
{
	frontLeftMotor->Set(0);
	rearLeftMotor->Set(0);
	frontRightMotor->Set(0);
	rearRightMotor->Set(0);
}
