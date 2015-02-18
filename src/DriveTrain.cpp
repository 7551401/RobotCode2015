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
	backwardRobot->SetSafetyEnabled(false);
	forwardRobot->SetSafetyEnabled(false);
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
	//leftEncoder = new Encoder (24,25, true, CounterBase:: k4X);
	///rightEncoder = new Encoder (16,17, true, CounterBase:: k4X);
	//leftEncoder->SetDistancePerPulse(123.4/891.15);
	//rightEncoder->SetDistancePerPulse(123.4/1584.4);
	//leftEncoder->Reset();
	//rightEncoder->Reset();

};
void DriveTrain::AutonomousInit(){
	leftEncoder->Reset();
	rightEncoder->Reset();
}
void DriveTrain::TeleopInit(){
	//leftEncoder->Reset();
	//rightEncoder->Reset();
}

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
		backwardRobot->SetSafetyEnabled(true);
		forwardRobot->SetSafetyEnabled(false);
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
		backwardRobot->SetSafetyEnabled(false);
		forwardRobot->SetSafetyEnabled(true);
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

	if (stick->GetRawButton(5)) {
		ReverseControls();
	}

	if (stick->GetRawButton(3)) {
		ForwardControls();
	}
	/*SmartDashboard::PutNumber("Total Distance, left", leftEncoder->GetDistance());
			SmartDashboard::PutNumber("Distance per Second, left", leftEncoder->GetRate());

			SmartDashboard::PutNumber("Total Distance, right", rightEncoder->GetDistance());
			SmartDashboard::PutNumber("Distance per Second, right", rightEncoder->GetRate());*/
}

//Driving in Autonomous
void DriveTrain::DriveAuto() {
	myRobot->ArcadeDrive(1.0,0.0,true);
}

void DriveTrain::DriveSet(float speed, float angle){
	myRobot->ArcadeDrive(speed,angle,true);
	//SmartDashboard::PutNumber("LD", leftEncoder->GetDistance());
	//SmartDashboard::PutNumber("RD", rightEncoder->GetDistance());
}

void DriveTrain::Right90(){
	myRobot->ArcadeDrive(0.0,1.0,true);}

