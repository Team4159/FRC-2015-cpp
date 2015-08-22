#include "WPILib.h"

#ifndef FRC2015TEAM4159_AUTOBALANCER_H_
#define FRC2015TEAM4159_AUTOBALANCER_H_

class AutoBalancer {
private:
	static const double OFF_BALANCE_ANGLE;
	static const double ON_BALANCE_ANGLE;

	static double angle_in_radians;
	static double driveMagnitude;
public:
	static void balanceFeed(float angle);
};

#endif
