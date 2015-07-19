#include "OctoDrive.h"

int OctoDrive::MECANUM_DRIVE = 1;
int OctoDrive::TANK_DRIVE = 2;
int OctoDrive::BACK_EXTEND_DRIVE = 3;

RobotDrive *OctoDrive::autoDrive;
RobotDrive *OctoDrive::strafeDrive;

OctoDrive::OctoDrive(DriveWheels *wheelSet, DrivePistons *pistonSet)
{
	frontLeft = wheelSet->frontLeftMotor;
	rearLeft = wheelSet->rearLeftMotor;
	frontRight = wheelSet->frontRightMotor;
	rearRight = wheelSet->rearRightMotor;

	frontLeftInverted = false;
	rearLeftInverted = false;
	frontRightInverted = false;
	rearRightInverted = false;
	leftSideInverted = false;
	rightSideInverted = false;
	isMecanum = false;

	OctoShift = pistonSet;

	autoDrive = new RobotDrive(frontLeft, rearLeft, frontRight, rearRight);
	strafeDrive = new RobotDrive(frontRight, frontLeft, rearRight, rearLeft);
}

OctoDrive::~OctoDrive(void)
{
	delete frontLeft;
	delete rearLeft;
	delete frontRight;
	delete rearRight;
	delete OctoShift;
	delete autoDrive;
	delete strafeDrive;
}

void OctoDrive::octoShift(int state) {
	isMecanum = state;
	if (isMecanum == MECANUM_DRIVE) {
	OctoShift->linearActuate(false); // Changes to mecanum
	} else if (isMecanum == TANK_DRIVE) {
	OctoShift->linearActuate(true); // Changes to tank (full)
	} else {
	OctoShift->backActuate(true); // Extends back pistons
	}
}

void OctoDrive::manualDrive(double xVal1, double yVal1, double xVal2, double yVal2) { // Drives the robot in a mecanum/tank mode
	if (isMecanum == MECANUM_DRIVE) { // Value Dictates the type of drive
										// you are using
		double right = (xVal1 > 0 ? xVal1 * xVal1 : -(xVal1 * xVal1)); // Acceleration
																		// curve
		double forward = (yVal1 > 0 ? yVal1 * yVal1 : -(yVal1 * yVal1));
		double clockwise = xVal2 * -0.75; // Decreased sensitivity

		double front_left = forward + clockwise + right;
		double front_right = forward - clockwise - right;
		double rear_left = forward + clockwise - right;
		double rear_right = forward - clockwise + right;

		double max = abs(front_left);
		if (abs(front_right) > max) {
			max = abs(front_right);
		}
		if (abs(rear_left) > max) {
			max = abs(rear_left);
		}
		if (abs(rear_right) > max) {
			max = abs(rear_right);
		}

		if (max > 1) {
			front_left /= max;
			front_right /= max;
			rear_left /= max;
			rear_right /= max;
		}

		if (frontLeftInverted) { // Motor inversion
			front_left = -front_left;

		}
		if (rearLeftInverted) {
			rear_left = -rear_left;
		}
		if (frontRightInverted) {
			front_right = -front_right;
		}
		if (rearRightInverted) {
			rear_right = -rear_right;
		}

		frontLeft->Set(front_left);
		rearLeft->Set(rear_left);
		frontRight->Set(front_right);
		rearRight->Set(rear_right);

	} else { // Tank driving code
		double leftVelocity = (yVal1 > 0 ? yVal1 * yVal1 : -(yVal1 * yVal1));
		double rightVelocity = (yVal2 > 0 ? yVal2 * yVal2
				: -(yVal2 * yVal2));

		if (leftSideInverted) {
			leftVelocity = -leftVelocity;
		}
		if (rightSideInverted) {
			rightVelocity = -rightVelocity;
		}

		frontLeft->Set(leftVelocity);
		rearLeft->Set(leftVelocity);
		frontRight->Set(rightVelocity);
		rearRight->Set(rightVelocity);

	}
}

void OctoDrive::invertMotor(int motorName, bool isInverted) { // Motor inversion method, changes boolean value
	switch (motorName) { // to indicated a motor's inversion, the driving code
	case OctoDrive::Motors::FrontLeft: // Will react accordingly
		frontLeftInverted = isInverted;
		break; // Note: the frontLeft, rearLeft... etc methods are for
	case OctoDrive::Motors::RearLeft: // Mecanum inversion, leftSide and rightSide for tank
		rearLeftInverted = isInverted; // Motor inversion
		break;
	case OctoDrive::Motors::FrontRight:
		frontRightInverted = isInverted;
		break;
	case OctoDrive::Motors::RearRight:
		rearRightInverted = isInverted;
		break;
	case OctoDrive::Motors::LeftSide:
		leftSideInverted = isInverted;
		break;
	case OctoDrive::Motors::RightSide:
		rightSideInverted = isInverted;
		break;
	default:
		break;
	}
}
