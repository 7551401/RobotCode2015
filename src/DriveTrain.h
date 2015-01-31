/*
 * DriveTrain.h
 *
 *  Created on: Jan 31, 2015
 *      Author: Peter
 */

#ifndef _DRIVETRAIN_H_
#define _DRIVETRAIN_H_

class DriveTrain {
	Victor *vic1;
	Victor *vic2;
	Victor *vic3;
	Victor *vic4;
	Joystick *stick;
	RobotDrive *myRobot;


public:
	DriveTrain();
	void DriveOriented();
	void DriveAuto();
	double getThrottle(double);
};

#endif
