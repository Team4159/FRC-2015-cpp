#include "IO.h"

Joystick *IO::leftStick = new Joystick(1);
Joystick *IO::rightStick = new Joystick(2);
Joystick *IO::secondaryStick = new Joystick(3);

DriveWheels *IO::wheelSet = new DriveWheels(0, 1, 2, 3);
DrivePistons *IO::pistonSet = new DrivePistons(0, 1, 2, 3);
OctoDrive *IO::mainDrive = new OctoDrive(wheelSet, pistonSet);

ToteLifter *IO::elevator = new ToteLifter(4, 5);

DigitalInput *IO::lowLimit = new DigitalInput(8);
DigitalInput *IO::highLimit = new DigitalInput(9);
DigitalInput *IO::toteSensor = new DigitalInput(7);

void IO::init(void)
{
	mainDrive->octoShift(OctoDrive::MECANUM_DRIVE);
	mainDrive->invertMotor(OctoDrive::Motors::RearRight, false);
	mainDrive->invertMotor(OctoDrive::Motors::FrontRight, false);
	mainDrive->invertMotor(OctoDrive::Motors::FrontLeft, true);
	mainDrive->invertMotor(OctoDrive::Motors::RearLeft, true);
	mainDrive->invertMotor(OctoDrive::Motors::LeftSide, true);
	mainDrive->invertMotor(OctoDrive::Motors::RightSide, false);

	elevator->setHighLow(lowLimit, highLimit);
}
