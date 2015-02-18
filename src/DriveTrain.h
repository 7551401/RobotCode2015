#ifndef _DRIVETRAIN_H_
#define _DRIVETRAIN_H_

class DriveTrain {
	Victor *vic1;
	Victor *vic2;
	Victor *vic3;
	Victor *vic4;
	Victor *vic5;
	Victor *vic6;
	Joystick *stick;
	Joystick *xbox;
	RobotDrive *myRobot;
	RobotDrive *forwardRobot;
	RobotDrive *backwardRobot;
	bool IsForward;
	Encoder *leftEncoder;
	Encoder *rightEncoder;


public:
	DriveTrain();
	void DriveOriented();
	void LiftElevator();
	void DriveAuto();
	double getThrottle(double);
	void DriveSet(float, float);
	void ReverseControls();
	void ForwardControls();
	void AutonomousInit();
	void TeleopInit();
	void Right90();
};

#endif
