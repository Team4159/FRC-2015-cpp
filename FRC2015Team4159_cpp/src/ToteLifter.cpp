#include "ToteLifter.h"

ToteLifter::ToteLifter(Victor *leftMotor, Victor *rightMotor)
{
	leftLifter = leftMotor;
	rightLifter = rightMotor;
}

ToteLifter::ToteLifter(int leftChannel, int rightChannel)
{
	leftLifter = new Victor(leftChannel);
	rightLifter = new Victor(rightChannel);
}

ToteLifter::~ToteLifter(void)
{
	delete leftLifter;
	delete rightLifter;
	delete lowLimit;
	delete topLimit;
}

void ToteLifter::manualLift(double velocity)
{
	leftLifter->Set(-velocity);
	rightLifter->Set(velocity);
}

void ToteLifter::setHighLow(DigitalInput *lowSensor, DigitalInput *topSensor)
{
	lowLimit = lowSensor;
	topLimit = topSensor;
}

void ToteLifter::setHighLow(int lowChannel, int topChannel)
{
	lowLimit = new DigitalInput(lowChannel);
	topLimit = new DigitalInput(topChannel);
}

void ToteLifter::autoLift(double velocity)
{
	if (velocity > 0) {

		if (!topLimit->Get()) { // Checks if top limit switch is pressed if
								// positive value
			manualLift(0.0); // If not, it continues
		} else {
			manualLift(velocity);
		}

	} else if (velocity < 0) {

		if (!lowLimit->Get()) {
			manualLift(0.0);
		} else {
			manualLift(velocity); // Checks if low limit switch is pressed
									// if negative value
		} // If not, it continues

	} else {
		manualLift(0.0); // If value is not greater or less, then it is 0,
							// meaning a stop
	}
}

void ToteLifter::moveLow(void)
{
	while (lowLimit->Get()) {
		manualLift(-1.0);
	}
	manualLift(0.0);
}
