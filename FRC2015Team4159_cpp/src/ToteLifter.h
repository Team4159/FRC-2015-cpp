#include "WPILib.h"

#ifndef FRC2015TEAM4159_TOTELIFTER_H_
#define FRC2015TEAM4159_TOTELIFTER_H_

class ToteLifter {
private:
	Victor *leftLifter;
	Victor *rightLifter;

	DigitalInput *lowLimit;
	DigitalInput *topLimit;
public:
	ToteLifter(Victor *leftMotor, Victor *rightMotor);
	ToteLifter(int leftChannel, int rightChannel);
	~ToteLifter(void);

	void manualLift(double velocity);
	void setHighLow(DigitalInput *lowSensor, DigitalInput *topSensor);
	void setHighLow(int lowChannel, int topChannel);
	void autoLift(double velocity);
	void moveLow(void);
};

#endif
