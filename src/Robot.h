#include "WPILib.h"
#include "AHRS.h"

#ifndef FRC2015TEAM4159_ROBOT_H_
#define FRC2015TEAM4159_ROBOT_H_

class Robot: public IterativeRobot
{
public:
	static AHRS *imu;

	void RobotInit(void);
	void AutonomousInit(void);
	void AutonomousPeriodic(void);
	void TeleopInit(void);
	void TeleopPeriodic(void);
	void TestInit(void);
	void TestPeriodic(void);

private:
	LiveWindow *lw;

	//Switch values
	static bool ifSixDown;
	static bool ifSevenDown;

	bool firstIteration;
	bool isCalibrating;
	double elevatorValue;

	//Auto presets
	static double autoMotorPower;
	static double autoMotorTime;
	static bool autoPickup;
	static double autoPickupTime;
	bool firstRun;

	//Random stuff for auto
	static Timer *autoTime;
	static double travelTime;
	static double rejoinRouteTime;
	static double liftTime;
	static double exitTime;
	static double toteDropTime;
	static double giveupTime;
	static double Kp;
	static double drivetrainOffset;

	static void toteTimedLift(double liftTime);
	static void straightDrive(double speed, double duration);
	static void toteGet(double speed);
	static void straightDrive(double speed, double duration, double offset);
	static void toteGet(double speed, double offset);
	static void autoStrafe(double speed, double duration);
	static void continuedRoutine(bool ifGyro);
	static void endRoutine(bool ifGyro);
	static void runRoutine(int autoChoice);
};

#endif
