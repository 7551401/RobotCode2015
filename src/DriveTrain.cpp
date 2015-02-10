#include "WPILib.h"
#include "DriveTrain.h"

DriveTrain::DriveTrain() {
	vic1 = new Victor(3);
	vic2= new Victor(2);
	vic3= new Victor(1);
	vic4= new Victor(0);
	myRobot= new RobotDrive(vic1,vic2,vic3,vic4);
	stick = new Joystick(0);

	//Motors are inverted because the motors were initially messed up
	myRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	myRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

};

double DriveTrain::getThrottle(double val){
	 float throttle = stick->GetThrottle();
	 throttle++;
	 throttle = throttle *((1-val)/2);
	 throttle+= val;
	 return throttle;

	}

//Driving in Teleop
void DriveTrain::DriveOriented() {
	//Scales the Joystick values by the throttle value
	float throttle = getThrottle(.5);
	myRobot->ArcadeDrive(stick->GetY()*throttle, stick->GetTwist()*throttle, true);
};

//Driving in Autonomous
void DriveTrain::DriveAuto() {
	myRobot->ArcadeDrive(1.0,0.0,true);
}

void DriveTrain::DriveSet(float speed, float angle){
	myRobot->ArcadeDrive(speed,angle,true);
}
