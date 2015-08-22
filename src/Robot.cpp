#include "Robot.h"

#include "IO.h"
#include "AutoBalancer.h"
#include "AutoChooser.h"

AHRS *Robot::imu;

bool Robot::ifSixDown = false;
bool Robot::ifSevenDown = false;

double Robot::autoMotorPower = 0.5;
double Robot::autoMotorTime = 2.5;
bool Robot::autoPickup = true;
double Robot::autoPickupTime = 2.0;

Timer *Robot::autoTime = new Timer();
double Robot::travelTime = 1.0;
double Robot::rejoinRouteTime = 1.0;
double Robot::liftTime = 1.0;
double Robot::exitTime = 3.0;
double Robot::toteDropTime = 1.0;
double Robot::giveupTime = 3.0;
double Robot::Kp = 0.00278;
double Robot::drivetrainOffset = 0.1;

void Robot::RobotInit(void)
{
	IO::init();

	lw = LiveWindow::GetInstance();
	try {
		uint8_t update_rate_hz = 50;
		imu = new AHRS(SerialPort::kUSB, update_rate_hz);
		firstIteration = true;
	} catch (...)
	{
		firstIteration = false;
	}

	if (imu->IsConnected()) {
		SmartDashboard::PutBoolean("First Iteration Of Gyro Complete", true);
		lw->AddSensor("IMU", "Gyro", imu);
	} else {
		SmartDashboard::PutBoolean("First Iteration Of Gyro Complete", false);
	}

}

void Robot::AutonomousInit(void)
{
	IO::mainDrive->octoShift(OctoDrive::MECANUM_DRIVE);
	firstRun = true;
}

void Robot::AutonomousPeriodic(void)
{
	if (firstIteration && !imu->IsCalibrating())
				;
			{ // Wait for imu gyro to calibrate
				Wait(0.3);
				imu->ZeroYaw();
				firstIteration = false;
			}

			if (firstRun) { // Drive teh auto!!!
				if (autoPickup)
					toteTimedLift(autoPickupTime);
				straightDrive(autoMotorPower, autoMotorTime);
				firstRun = false;
			}
}

void Robot::TeleopInit()
{
	elevatorValue = 1.0;
	ifSixDown = false;
	ifSevenDown = false;
}

void Robot::TeleopPeriodic()
{
	SmartDashboard::PutNumber("Yaw Value", imu->GetYaw());
	SmartDashboard::PutNumber("Pitch Value", imu->GetPitch());
	SmartDashboard::PutNumber("Roll Value", imu->GetRoll());

	SmartDashboard::PutBoolean("Tote Sensed?", !IO::toteSensor->Get());

	if (IO::leftStick->GetRawButton(3)) { // Changes to tank

		IO::mainDrive->octoShift(OctoDrive::TANK_DRIVE);
		SmartDashboard::PutString("Drive State:", "Traction/Tank");

	} else if (IO::leftStick->GetRawButton(2)) { // Changes to mecanum

		IO::mainDrive->octoShift(OctoDrive::MECANUM_DRIVE);
		SmartDashboard::PutString("Drive State:", "Mecanum");

	} else if (IO::leftStick->GetRawButton(5)) { // Raises back set piston set
												// and changes control to
												// tank

		IO::mainDrive->octoShift(OctoDrive::BACK_EXTEND_DRIVE);
		SmartDashboard::PutString("Drive State:", "Back Traction, Front Mecanum/Tank");

	}

	IO::mainDrive->manualDrive(-IO::leftStick->GetX(), IO::leftStick->GetY(),
			IO::rightStick->GetX(), IO::rightStick->GetY()); // Drives according
															// to
															// tank/mecanum
															// boolean in
															// OctoDrive

	if (!ifSixDown && IO::secondaryStick->GetRawButton(6)) {
		if (elevatorValue < 1.0) {
			elevatorValue = elevatorValue + 0.2;
		}
		if (elevatorValue > 1.0) {
			elevatorValue = 1.0;
		}
		ifSixDown = true;
	} else if (ifSixDown && !IO::secondaryStick->GetRawButton(6)) {
		ifSixDown = false;
	}

	if (!ifSevenDown && IO::secondaryStick->GetRawButton(7)) {
		if (elevatorValue > 0.6) {
			elevatorValue = elevatorValue - 0.2;
		}
		if (elevatorValue < 0.6) {
			elevatorValue = 0.6;
		}
		ifSevenDown = true;
	} else if (ifSevenDown && !IO::secondaryStick->GetRawButton(7)) {
		ifSevenDown = false;
	}

	if (IO::secondaryStick->GetRawButton(3) || IO::rightStick->GetRawButton(3)) { // Moves elevator up
		IO::elevator->autoLift(elevatorValue);
	} else if (IO::secondaryStick->GetRawButton(2) || IO::rightStick->GetRawButton(2)) { // Moves elevator down
		IO::elevator->autoLift(-elevatorValue);
	} else {
		IO::elevator->autoLift(0.0); // Stops elevator if there is no joystick
									// input
	}

	AutoBalancer::balanceFeed(-1 * imu->GetRoll());

	SmartDashboard::PutNumber("Elevator_Speed", elevatorValue * 100);
	SmartDashboard::PutBoolean("Upper Limit Reached", !IO::highLimit->Get());
	SmartDashboard::PutBoolean("Lower Limit Reached", !IO::lowLimit->Get());
}

void Robot::TestInit()
{
	IO::mainDrive->octoShift(OctoDrive::MECANUM_DRIVE); // Shifts to mecanum
	firstRun = true;
}

void Robot::TestPeriodic()
{
	lw->Run();
}

void Robot::toteTimedLift(double liftTime) {
	IO::elevator->moveLow();
	autoTime->Reset();
	autoTime->Start();
	while (autoTime->Get() < liftTime) {
		IO::elevator->autoLift(1.0);
	}
	autoTime->Stop();
	autoTime->Reset();
	IO::elevator->autoLift(0.0);
}

void Robot::straightDrive(double speed, double duration) {
	autoTime->Reset();
	autoTime->Start();
	while (autoTime->Get() < duration) {
		OctoDrive::autoDrive->Drive(speed, -Kp * imu->GetYaw());
	}
	OctoDrive::autoDrive->Drive(0.0, 0.0);
	autoTime->Stop();
}

void Robot::toteGet(double speed) {
	autoTime->Reset();
	autoTime->Start();
	while (IO::toteSensor->Get()) {
		OctoDrive::autoDrive->Drive(speed, -Kp * imu->GetYaw());
		if (autoTime->Get() > giveupTime) {
			break;
		}
	}
	OctoDrive::autoDrive->Drive(0.0, 0.0);
	autoTime->Stop();
}

void Robot::straightDrive(double speed, double duration, double offset) {
	autoTime->Reset();
	autoTime->Start();
	while (autoTime->Get() < duration) {
		OctoDrive::autoDrive->Drive(speed, offset);
	}
	OctoDrive::autoDrive->Drive(0.0, 0.0);
	autoTime->Stop();
	autoTime->Reset();
}

void Robot::toteGet(double speed, double offset) {
	autoTime->Reset();
	autoTime->Start();
	while (IO::toteSensor->Get()) {
		OctoDrive::autoDrive->Drive(speed, offset);

		if (autoTime->Get() > giveupTime) {
			break;
		}
	}
	OctoDrive::autoDrive->Drive(0.0, 0.0);
	autoTime->Stop();
}

void Robot::autoStrafe(double speed, double duration) {
	autoTime->Reset();
	autoTime->Start();

	while (autoTime->Get() < duration) {
		OctoDrive::strafeDrive->Drive(0.5, -Kp * imu->GetYaw());
	}
	autoTime->Stop();
	autoTime->Reset();
	IO::wheelSet->stopAll();
}

void Robot::continuedRoutine(bool ifGyro) {
	if (ifGyro) {
		toteGet(0.5);
		IO::elevator->moveLow();
		toteTimedLift(liftTime);
		autoStrafe(0.5, rejoinRouteTime);
		straightDrive(0.5, travelTime);
		autoStrafe(-0.5, rejoinRouteTime);

	} else {
		toteGet(0.5, drivetrainOffset);
		IO::elevator->moveLow();
		toteTimedLift(liftTime);
		autoStrafe(0.5, rejoinRouteTime);
		straightDrive(0.5, travelTime, drivetrainOffset);
		autoStrafe(-0.5, rejoinRouteTime);
	}
}

void Robot::endRoutine(bool ifGyro) {
	if (ifGyro) {
		toteGet(0.5);
		IO::elevator->moveLow();
		toteTimedLift(liftTime);
		autoStrafe(0.5, exitTime);
		IO::elevator->moveLow();
		straightDrive(-0.5, toteDropTime);
	} else {
		toteGet(0.5, drivetrainOffset);
		IO::elevator->moveLow();
		toteTimedLift(liftTime);
		autoStrafe(0.5, exitTime);
		IO::elevator->moveLow();
		straightDrive(-0.5, toteDropTime, drivetrainOffset);
	}
}

void Robot::runRoutine(int autoChoice) {
	switch (autoChoice) {
	case AutoChooser::Choices::MOVE_ONLY:
		straightDrive(0.5, 2, -0.05);
		break;
	case AutoChooser::Choices::PICK_THREE_TOTE:
		continuedRoutine(imu->IsConnected());
		continuedRoutine(imu->IsConnected());
		endRoutine(imu->IsConnected());
		break;
	default:
		break;
	}
}

START_ROBOT_CLASS(Robot);
