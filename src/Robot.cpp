#include "WPILib.h"
#include "DriveTrain.h"
#include "SmartDashboard/SendableChooser.h"
class Robot: public IterativeRobot{
private:
	SerialPort *sonicSensor;
	Encoder *leftEncoder;
	Encoder *rightEncoder;
	LiveWindow *lw;
	Timer *time;
	Joystick *stick;
	Joystick *xbox;
	DriveTrain * Drive;
	Jaguar *jag1;
	Jaguar *jag2;
	JoystickButton *button1;
	JoystickButton *button2;
	JoystickButton *button3;
	Timer *timer;
	SendableChooser *chooser;
	int AutoCode;
	double y=0.0;
	void RobotInit(){
		sonicSensor = new SerialPort(9600);
		sonicSensor->SetFlowControl(SerialPort::kFlowControl_None);
		sonicSensor->EnableTermination(0x13);
		Drive = new DriveTrain();
		stick = new Joystick(0);
		xbox = new Joystick(1);
		// leftEncoder = new Encoder (24,25, true, CounterBase:: k4X); // game robot
		// rightEncoder = new Encoder (16,17, true, CounterBase:: k4X); // game robot
		leftEncoder = new Encoder (2,3, true, CounterBase:: k4X); // practice robot
		rightEncoder = new Encoder (0,1, true, CounterBase:: k4X); // practice robot
		leftEncoder->SetDistancePerPulse(123.4/891.15);
		rightEncoder->SetDistancePerPulse(123.4/1584.4);
		chooser = new SendableChooser();
		chooser->AddDefault("Do nothing", (void*)1);
		chooser->AddObject("Drive Forward" , (void*)2);
		chooser->AddObject("One tote, one can, or both", (void*)3);
		chooser->AddObject("two totes from landfill", (void*)4);
		chooser->AddObject("One can from platform", (void*)5);
		SmartDashboard::PutData("Autonomous modes", chooser);
		leftEncoder->Reset();
		rightEncoder->Reset();
		jag1= new Jaguar(4);
		jag2= new Jaguar(5);}
	void AutonomousInit(){
		AutoCode = (int)(chooser->GetSelected());
		time= new Timer();
		time->Start();
		y=0;}
	void AutonomousPeriodic(){
		switch(AutoCode){
			case 1: doNothing();
			break;
			case 2: driveForward();
			break;
			case 3: oneTote();
			break;
			case 4: twoTotes();
			break;
			case 5: oneCan();
			break;}}
	void twoTotes(){
		if (time->Get()<1.0)
			Drive->DriveSet(.75,0.0);
		else if (time->Get()<2.0){
			jag1->SetSpeed(-1.0);
			jag2->SetSpeed(-1.0);}
		else if (time->Get()<3.0)
			driveForward();
		else
			Drive->DriveSet(0.0,0.0);}
	void oneCan(){
		if (time->Get()<1.0){
			jag1->SetSpeed(-1.0);
			jag2->SetSpeed(-1.0);}
		else if (time->Get()<2.0)
			Drive->DriveSet(.75,0.0);
		else if (time->Get()<3.0){
			jag1->SetSpeed(1.0);
			jag2->SetSpeed(1.0);}
		else if (time->Get()<4.0){
			driveForward();}}
	void doNothing(){
		Drive->DriveSet(0.0,0.0);}
	void driveForward(){
		if (leftEncoder->GetDistance()<105 && leftEncoder->GetDistance()>-105 && rightEncoder->GetDistance()>-105 && rightEncoder->GetDistance() <105){
			Drive->DriveSet(-0.75,0.0);}
		else
			Drive->DriveSet(0.0,0.0);
		SmartDashboard::PutNumber("left", leftEncoder->GetDistance());
		SmartDashboard::PutNumber("right" , rightEncoder->GetDistance());}
	void oneTote(){
		if (time->Get()<2.0){
			jag1->SetSpeed(-1.0);
			jag2->SetSpeed(-1.0);}
		else if (time->Get()<3.0){
			driveForward();}
		/*Used to set down the totes; DO NOT DELETE this comment
		 *
		 * else if (time->Get()<5.0){
			jag1->SetSpeed(1.0);
			jag2->SetSpeed(1.0);}
		else if (time->Get()<5.3){
			Drive->DriveSet(-0.5,0.0);}
		else
			Drive->DriveSet(0.0,0.0);*/}
	void TeleopInit(){
		y=0;
		rightEncoder->Reset();
		leftEncoder->Reset();}
	void TeleopPeriodic(){
		char buffer[8];
		uint32_t bytes = sonicSensor -> Read(buffer, 5);
		SmartDashboard::PutNumber("Sonic sensor bytes", bytes);
		if (bytes > 0){


		SmartDashboard::PutNumber("Sonic sensor byte 1", buffer[0]);
		}
		static float maxLeft = 0.0;
		static float maxRight = 0.0;
		SmartDashboard::PutNumber("Total Distance, left", leftEncoder->GetDistance());
		SmartDashboard::PutNumber("Distance per Second, left", leftEncoder->GetRate());
		if (maxLeft < leftEncoder->GetRate()) maxLeft = leftEncoder->GetRate();
		SmartDashboard::PutNumber("Max Distance per Second, left", maxLeft);
		SmartDashboard::PutNumber("Total Distance, right", rightEncoder->GetDistance());
		SmartDashboard::PutNumber("Distance per Second, right", rightEncoder->GetRate());
		if (maxRight < rightEncoder->GetRate()) maxRight = rightEncoder->GetRate();
		SmartDashboard::PutNumber("Max Distance per Second, right", maxRight);
		float lifterSpeed = xbox->GetRawAxis(5);
		float lifterRatio = -1.0;
		if (lifterSpeed < 0) lifterRatio *= -1.0;
		lifterSpeed = lifterSpeed * lifterSpeed * lifterRatio;
		if (xbox->GetRawAxis(5) >= 0.1){
			jag1->SetSpeed(lifterSpeed);
			jag2->SetSpeed(lifterSpeed);}
		else if (xbox->GetRawAxis(5) <= -0.1){
			jag1->SetSpeed(lifterSpeed);
			jag2->SetSpeed(lifterSpeed);}
		else{
			jag1->SetSpeed(0.0);
			jag2->SetSpeed(0.0);}
		Drive->DriveOriented();}
	void TestPeriodic(){
		lw->Run();}};
START_ROBOT_CLASS(Robot);
