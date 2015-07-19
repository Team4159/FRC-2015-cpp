#include "WPILib.h"
#include <string>
#include <cmath>
#include "DrivePistons.h"
#include "DriveWheels.h"

#ifndef FRC2015TEAM4159_OCTODRIVE_H_
#define FRC2015TEAM4159_OCTODRIVE_H_

class OctoDrive
{
private:
	Victor *frontLeft;
	Victor *rearLeft;
	Victor *frontRight;
	Victor *rearRight;

	DrivePistons *OctoShift;

	int isMecanum;
	bool frontLeftInverted;
	bool rearLeftInverted;
	bool frontRightInverted;
	bool rearRightInverted;
	bool leftSideInverted;
	bool rightSideInverted;
public:
	static RobotDrive *autoDrive;
	static RobotDrive *strafeDrive;

	static int MECANUM_DRIVE;
	static int TANK_DRIVE;
	static int BACK_EXTEND_DRIVE;

	enum Motors {
		FrontLeft, RearLeft, FrontRight, RearRight, RightSide, LeftSide
	};

	OctoDrive(DriveWheels *wheelSet, DrivePistons *pistonSet);
	~OctoDrive(void);

	void octoShift(int state);
	void manualDrive(double xVal1, double yVal1, double xVal2, double yVal2);
	void invertMotor(int motorName, bool isInverted);
};

#endif
