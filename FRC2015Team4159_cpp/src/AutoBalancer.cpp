#include "AutoBalancer.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Robot.h"
#include "OctoDrive.h"

double AutoBalancer::angle_in_radians;
double AutoBalancer::driveMagnitude;

const double AutoBalancer::OFF_BALANCE_ANGLE = 25;
const double AutoBalancer::ON_BALANCE_ANGLE = 10;

void AutoBalancer::balanceFeed(float angle)
{
	if (angle > OFF_BALANCE_ANGLE) {
				while (angle > ON_BALANCE_ANGLE) {
					SmartDashboard::PutBoolean("Auto-Balance_Engaged", true);
					angle_in_radians = angle * M_PI / 180;
					driveMagnitude = -1 * sin(angle_in_radians);

					OctoDrive::autoDrive->Drive(driveMagnitude, 0.0);
					angle = -1 * Robot::imu->GetRoll();
				}
			}

			SmartDashboard::PutBoolean("Auto-Balance_Engaged", false);
}
