#include "WPILib.h"
#include "AHRS.h"
#include "DriveWheels.h"
#include "DrivePistons.h"
#include "OctoDrive.h"
#include "ToteLifter.h"

#ifndef FRC2015TEAM4159_IO_H_
#define FRC2015TEAM4159_IO_H_

class  IO
{
public:
	static Joystick *leftStick;
	static Joystick *rightStick;
	static Joystick *secondaryStick;

	static DriveWheels *wheelSet;
	static DrivePistons *pistonSet;
	static OctoDrive *mainDrive;

	static ToteLifter *elevator;

	static DigitalInput *lowLimit;
	static DigitalInput *highLimit;

	static DigitalInput *toteSensor;

	static void init(void);
};

#endif
