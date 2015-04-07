#include "WPILib.h"
#include "DriveTrain.h"
DriveTrain::DriveTrain(){
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
	forwardRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	forwardRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);


	forwardRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	forwardRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	backwardRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	backwardRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	backwardRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);

	cameraServo = new Servo (6);
	backwardRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	IsForward = true;};
void DriveTrain::AutonomousInit(){
	leftEncoder->Reset();
	rightEncoder->Reset();}


void DriveTrain::TeleopInit(){}
double DriveTrain::getThrottle(double val){
	 float throttle = stick->GetThrottle();
	 throttle++;
	 throttle = throttle *((1-val)/2);


	 throttle+= val;
	 return throttle;}
void DriveTrain::ReverseControls(){
	if(IsForward){
		myRobot = backwardRobot;


		backwardRobot->SetSafetyEnabled(true);
		forwardRobot->SetSafetyEnabled(false);
		IsForward = false;}}
void DriveTrain::ForwardControls() {
	if (!IsForward) {


		myRobot = forwardRobot;
		IsForward = true;
		backwardRobot->SetSafetyEnabled(false);
		forwardRobot->SetSafetyEnabled(true);}}
void DriveTrain::DriveOriented() {


	float throttle = getThrottle(.4);
	float b= .5;
	float m= 1-b;
	float y=0;
	if (stick->GetY()>.2){
		y= stick->GetY()*m+b;}
	else if (stick->GetY()<-.2){
		y= stick->GetY()*m-b;
	}
	float c= .4;
	float n= 1-c;
	float x=0;
	if (stick->GetTwist()>.2)
	 x= stick->GetTwist()*n+c;
	else if (stick->GetTwist()<-.2)
			x= stick->GetTwist()*n-c;
	myRobot->ArcadeDrive(y*throttle, x*throttle,true);
	if (stick->GetX()<-.33){
		if (IsForward){
			vic1->SetSpeed(0.0);


			vic2->SetSpeed(0.0);}
		else{
			vic3->SetSpeed(0.0);
			vic4->SetSpeed(0.0);}}
	else if (stick->GetX()>.33){


		if (IsForward){
			vic3->SetSpeed(0.0);
			vic4->SetSpeed(0.0);}
		else{
			vic1->SetSpeed(0.0);


			vic2->SetSpeed(0.0);}}
	if (stick->GetRawButton(6)) {
		ReverseControls();
		cameraServo->SetAngle(0);}
	if (stick->GetRawButton(5)) {
		ForwardControls();
		cameraServo->SetAngle(180);}}


void DriveTrain::DriveAuto(){
	myRobot->ArcadeDrive(1.0,0.0,true);}
void DriveTrain::DriveSet(float speed, float angle){
	myRobot->ArcadeDrive(speed,angle,true);}
void DriveTrain::Turn(double speed, bool isRight){


	if (isRight){
		vic1->SetSpeed(speed);
		vic2->SetSpeed(speed);
		vic3->SetSpeed(speed);
		vic4->SetSpeed(speed);}


	else{
		vic1->SetSpeed(-speed);
		vic2->SetSpeed(-speed);
		vic3->SetSpeed(-speed);
		vic4->SetSpeed(-speed);}}
