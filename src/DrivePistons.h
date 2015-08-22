#include "WPILib.h"

#ifndef FRC2015TEAM4159_DRIVEPISTONS_H_
#define FRC2015TEAM4159_DRIVEPISTONS_H_

class DrivePistons
{
public:
	DoubleSolenoid *piston1;
	DoubleSolenoid *piston2;

	DrivePistons(DoubleSolenoid *solenoid1, DoubleSolenoid *solenoid2, DoubleSolenoid *solenoid3, DoubleSolenoid *solenoid4);
	DrivePistons(int channel1, int channel2, int channel3, int channel4);
	~DrivePistons(void);

	void linearActuate(bool isExtended);
	void backActuate(bool isExtended);
};

#endif
