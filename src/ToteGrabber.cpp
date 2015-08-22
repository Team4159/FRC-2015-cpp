#include "ToteGrabber.h"

ToteGrabber::ToteGrabber(Victor *tmp_leftGrab, Victor *tmp_rightGrab)
{
	leftGrabber = tmp_leftGrab;
	rightGrabber = tmp_rightGrab;
}

ToteGrabber::ToteGrabber(int leftChannel, int rightChannel)
{
	leftGrabber = new Victor(leftChannel);
	rightGrabber = new Victor(rightChannel);
}

void ToteGrabber::toteGrab(double velocity)
{
	leftGrabber->Set(-velocity);
	rightGrabber->Set(velocity);
}

void ToteGrabber::grabberDeploy(bool isActuated)
{
	if (isActuated) {
		rightActuate->Set(DoubleSolenoid::Value::kForward);
		leftActuate->Set(DoubleSolenoid::Value::kForward);
	} else {
		rightActuate->Set(DoubleSolenoid::Value::kReverse);
		leftActuate->Set(DoubleSolenoid::Value::kReverse);
	}
}
