#include "WPILib.h"
#include "DriveTrain.h"
#include "SmartDashboard/SendableChooser.h"
class Robot: public IterativeRobot{
private:


	Encoder *leftEncoder;
	Encoder *rightEncoder;
	LiveWindow *lw;
	Timer *time;
	Joystick *stick;


	Joystick *xbox;
	DriveTrain *Drive;
	Jaguar *jag1;
	Jaguar *jag2;
	JoystickButton *button1;


	JoystickButton *button2;
	JoystickButton *button3;
	Timer *timer;
	SendableChooser *chooser;
	int AutoCode;


	double y=0.0;
	int step=0;
	double leftStart=0.0;
	double rightStart=0.0;
	void RobotInit(){


		Drive = new DriveTrain();
		stick = new Joystick(0);
		xbox = new Joystick(1);
		// leftEncoder = new Encoder (24,25, true, CounterBase:: k4X); // game robot
		// rightEncoder = new Encoder (16,17, true, CounterBase:: k4X); // game robot

		leftEncoder = new Encoder (2,3, true, CounterBase:: k4X); // practice robot
		rightEncoder = new Encoder (0,1, true, CounterBase:: k4X); // practice robot
		leftEncoder->SetDistancePerPulse(-3.14/90); //game 123.4/891.15
		rightEncoder->SetDistancePerPulse(3.14/90); //game 123.4/1584.4
		chooser = new SendableChooser();


		chooser->AddDefault("Do nothing", (void*)1);
		chooser->AddObject("Drive Forward" , (void*)2);
		chooser->AddObject("one can @ start", (void*)3);
		chooser->AddObject("two totes from landfill", (void*)4);
		chooser->AddObject("One can from platform", (void*)5);


		chooser->AddObject("Two totes and One can", (void*)6);
		SmartDashboard::PutData("Autonomous modes", chooser);
		leftEncoder->Reset();
		rightEncoder->Reset();
		jag1= new Jaguar(4);


		jag2= new Jaguar(5);}
	void AutonomousInit(){
		AutoCode = (int)(chooser->GetSelected());
		time= new Timer();
		time->Start();


		step=1;
		leftEncoder->Reset();
		rightEncoder->Reset();
		rightStart=0.0;
		leftStart=0.0;}


	void AutonomousPeriodic(){
		SmartDashboard::PutNumber("left", leftEncoder->GetDistance());
		SmartDashboard::PutNumber("right" , rightEncoder->GetDistance());
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
			break;
			case 6: both();


			break;}}
	void both(){
		bool done= false;
		if (step==1){
			Drive->DriveSet(0.0,0.0);


			done =liftArms(2.0,-1.0);}
		else if (step==2)
			done= driveDistance(7,-.5);
		else if (step==3){
			done= liftArms(2.0,1.0);


			Drive->DriveSet(0.0,0.0);}
		else if (step==4)
			done= driveDistance(17,.5);
		else if (step==5)
			done=turn(true);


		else if (step==6)
			done= driveDistance(16,.5); //26??
		else if (step==7)
			done= turn(false);
		else if (step==8)


			done= driveDistance(17,.5);
		else if (step==9)
			done= liftArms(2.0,1.0);
		else if (step==10)
			done= driveDistance(36.0,-.75);


		else if (step==11)
			done= driveDistance(20.0,-.5);
		else if (step==12)
			done= driveDistance(16.0,-.45);
		else if (step==13)

			done= turn(false);
		else
			doNothing();
		nextStep(done);}
	void twoTotes(){


		bool done= false;
		if (step==1)
			done= driveDistance(12.0,.5);
		else if (step==2)
			done= liftArms(1.5,-1.0);


		else if (step==3)
			done= driveDistance(36.0,-.75);
		else if (step==4)
			done= driveDistance(20.0, -.5);
		else if (step==5)


			done= driveDistance(16.0, -.45);
		else if (step==6)
			done= turn(true);
		else
			doNothing();


		nextStep(done);}
	bool liftArms(double duration, double speed){
		bool done= false;
		if (time->Get()<duration){
			jag1->SetSpeed(speed);


			jag2->SetSpeed(speed);}
		else
			done= true;
		return done;}
	bool turn(bool isRight){


		bool done= false;
		double inches= 22.0;
		double leftDis= leftEncoder->GetDistance()-leftStart;
		double rightDis= rightEncoder->GetDistance()-rightStart;
		if (leftDis<inches && leftDis>-inches && rightDis<inches && rightDis>-inches)


			Drive->Turn(.5,isRight);
		else{
			Drive->DriveSet(0.0,0.0);
			done=true;}
		return done;}


	void nextStep(bool done){
		if (done){
			step++;
			time->Reset();
			leftStart=leftEncoder->GetDistance();


			rightStart= rightEncoder->GetDistance();}}
	void oneCan(){
		bool done= false;
		if (step==1){
			Drive->DriveSet(0.0,0.0);


			done =liftArms(2.0,-1.0);}
		else if (step==2)
			done= driveDistance(7,-.5);
		else if (step==3){
			done= liftArms(2.0,1.0);


			Drive->DriveSet(0.0,0.0);}
		else if (step==4)
			done= driveDistance(36.0,.75);
		else if (step==5)
			done= driveDistance(20.0,.5);


		else if (step==6)
			done= driveDistance(16.0,.45);
		else if (step==7)
			done= turn(true);
		else


			doNothing();
		nextStep(done);}
	void doNothing(){
		Drive->DriveSet(0.0,0.0);}
	bool driveDistance(int inches, double speed){


		bool done = false;
		double leftDis= leftEncoder->GetDistance()-leftStart;
		double rightDis= rightEncoder->GetDistance()-rightStart;
		if (leftDis<inches && leftDis>-inches && rightDis<inches && rightDis>-inches)
			Drive->DriveSet(speed,0.0);


		else{
			Drive->DriveSet(0.0,0.0);
			done=true;}
		return done;}
	void driveForward(){


		bool done= false;
		if (step==1)
			done = driveDistance(60, -.75);
		else if (step==2)
			done = driveDistance(25, -.5);


		else if (step==3)
			done = driveDistance(40, -.45);
		else if (step==4)
			done = turn(false);
		else


			doNothing();
		nextStep(done);
		SmartDashboard::PutNumber("left", leftEncoder->GetDistance());
		SmartDashboard::PutNumber("right" , rightEncoder->GetDistance());}
	void oneTote(){


		bool done= false;
		if (step==1)
			done= liftArms(2.0,-1.0);
		else if (step==2)
			done = driveDistance(60, -.75);


		else if (step==3)
			done = driveDistance(25, -.5);
		else if (step==4)
			done = driveDistance(40, -.4);
		else if (step==5)


			done = turn(true);
		else
			doNothing();
		nextStep(done);}
	void TeleopInit(){


		rightEncoder->Reset();
		leftEncoder->Reset();}
	void TeleopPeriodic(){
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
