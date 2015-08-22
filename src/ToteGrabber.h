#include "WPILib.h"

#ifndef FRC2015TEAM4159_TOTEGRABBER_H_
#define FRC2015TEAM4159_TOTEGRABBER_H_

class ToteGrabber {
private:
	Victor *leftGrabber;
	Victor *rightGrabber;
	DoubleSolenoid *rightActuate;
	DoubleSolenoid *leftActuate;
public:
	ToteGrabber(Victor *tmp_leftGrab, Victor *tmp_rightGrab);
	ToteGrabber(int leftChannel, int rightChannel);

	void toteGrab(double velocity);
	void grabberDeploy(bool isActuated);
};

#endif
