#include "DrivePistons.h"

DrivePistons::DrivePistons(DoubleSolenoid *solenoid1, DoubleSolenoid *solenoid2, DoubleSolenoid *solenoid3, DoubleSolenoid *solenoid4)
{
	piston1 = solenoid1;
	piston2 = solenoid2;
}

DrivePistons::DrivePistons(int channel1, int channel2, int channel3, int channel4)
{
	piston1 = new DoubleSolenoid(channel1, channel2);
	piston2 = new DoubleSolenoid(channel3, channel4);
}

DrivePistons::~DrivePistons(void)
{
	delete piston1;
	delete piston2;
}

void DrivePistons::linearActuate(bool isExtended)
{
	if (isExtended) {
		piston1->Set(DoubleSolenoid::Value::kForward);
		piston2->Set(DoubleSolenoid::Value::kForward);

	} else {
		piston1->Set(DoubleSolenoid::Value::kReverse);
		piston2->Set(DoubleSolenoid::Value::kReverse);

	}
}

void DrivePistons::backActuate(bool isExtended)
{
	if (isExtended) {
		piston1->Set(DoubleSolenoid::Value::kForward);
		piston2->Set(DoubleSolenoid::Value::kReverse);
	} else {
		piston1->Set(DoubleSolenoid::Value::kReverse);
		piston2->Set(DoubleSolenoid::Value::kReverse);
	}
}
