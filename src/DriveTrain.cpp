#include "WPILib.h"
#include "DriveTrain.h"

DriveTrain::DriveTrain() {
	vic1 = new Victor(3);
	vic2= new Victor(2);
	vic3= new Victor(1);
	vic4= new Victor(0);
	forwardRobot= new RobotDrive(vic1,vic2,vic3,vic4);
	backwardRobot = new RobotDrive(vic3, vic4, vic1, vic2);
	myRobot = backwardRobot;
	stick = new Joystick(0);

	//Motors are inverted because the motors were initially messed up
	forwardRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	forwardRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	forwardRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	forwardRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	backwardRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	backwardRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	backwardRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	backwardRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	//Sets boolean for joystick controls
	IsForward = true;

};

double DriveTrain::getThrottle(double val){
	 float throttle = stick->GetThrottle();
	 throttle++;
	 throttle = throttle *((1-val)/2);
	 throttle+= val;
	 return throttle;

	}

//Reverses controls if normal
void DriveTrain::ReverseControls() {
	if (IsForward) {

		myRobot = backwardRobot;
		IsForward = false;

		//myRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, false);
		//myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, false);
		//myRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, false);
		//myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, false);

	}
}

//Sets controls to normal if reversed
void DriveTrain::ForwardControls() {
	if (!IsForward) {
		//myRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
		//myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		//myRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		//myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

		myRobot = forwardRobot;
		IsForward = true;
	}
}

//Driving in Teleop
void DriveTrain::DriveOriented() {
	//Scales the Joystick values by the throttle value
	float throttle = getThrottle(.4);
	myRobot->ArcadeDrive(stick->GetY()*throttle, stick->GetTwist()*throttle,
			true);

	//forwardRobot->Feed();
	//backwardRobot->Feed();
	if (stick->GetX()<-.33) {
		if (IsForward) {
			vic1->SetSpeed(0.0);
			vic2->SetSpeed(0.0);
		} else {

			vic3->SetSpeed(0.0);
			vic4->SetSpeed(0.0);
		}
	}

	else if (stick->GetX()>.33) {
		if (IsForward) {
			vic3->SetSpeed(0.0);
			vic4->SetSpeed(0.0);
		} else {

			vic1->SetSpeed(0.0);
			vic2->SetSpeed(0.0);
		}
	}

	if (stick->GetRawButton(9)) {
		ReverseControls();
	}

	if (stick->GetRawButton(8)) {
		ForwardControls();
	}
};

//Driving in Autonomous
void DriveTrain::DriveAuto() {
	myRobot->ArcadeDrive(1.0,0.0,true);
}

void DriveTrain::DriveSet(float speed, float angle){
	myRobot->ArcadeDrive(speed,angle,true);
}
