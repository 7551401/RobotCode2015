#include "WPILib.h"
#include "DriveTrain.h"
#include "SmartDashboard/SendableChooser.h"
#include "PWM.h"

class Robot: public IterativeRobot{
private:

	Gyro *sandwich;
	Encoder *leftEncoder;
	Encoder *rightEncoder;
	LiveWindow *lw;
	Timer *time;
	Joystick *stick;

	Joystick *xbox;
	DriveTrain *Drive;
	Jaguar *jag1;
	Jaguar *jag2;
	Victor *twocan;
	JoystickButton *button1;

	PWM *LIDAR1;

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
		leftEncoder = new Encoder (24,25, true, CounterBase:: k4X); // game robot
		rightEncoder = new Encoder (16,17, true, CounterBase:: k4X); // game robot

		//leftEncoder = new Encoder (2,3, true, CounterBase:: k4X); // practice robot
		//rightEncoder = new Encoder (0,1, true, CounterBase:: k4X); // practice robot
		leftEncoder->SetDistancePerPulse(6.0*3.14/128.0); //game 123.4/891.15
		rightEncoder->SetDistancePerPulse(6.0*3.14/256.0); //game 123.4/1584.4
		chooser = new SendableChooser();


		chooser->AddDefault("Do nothing \n(Set in avoidable area)", (void*)1);
		chooser->AddObject("Toucan middle \n(Set middle frame on edge of ramp)" , (void*)2);
		chooser->AddObject("one can @ start \n(Place elev right under handle)", (void*)3);
		chooser->AddObject("two totes from landfill\n(Place middle frame on edge of ramp)", (void*)4);
		chooser->AddObject("One can from platform\n(18 inches away slightly slanted)", (void*)5);


		chooser->AddObject("One can from platform ramp\n(Middle frame on edge of ramp", (void*)7);
		chooser->AddObject("one yellow from start\n(Elevator just over yellow)", (void*)6);
		chooser->AddObject("Toucan Easy\n(See toucan middle)",(void*)8);
		chooser->AddObject("Toucan Hard\n(See toucan middle)",(void*)9);
		SmartDashboard::PutData("Autonomous modes", chooser);
		leftEncoder->Reset();
		rightEncoder->Reset();
		jag1= new Jaguar(4);

		twocan= new Victor(6);

		sandwich= new Gyro(0);
		sandwich->InitGyro();
		sandwich->Reset();

		jag2= new Jaguar(5);
		}
	void AutonomousInit(){
		AutoCode = (int)(chooser->GetSelected());
		time= new Timer();
		time->Start();
		sandwich->Reset();

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
			case 2: longArms();
			break;
			case 3: oneTote();
			break;


			case 4: twoTotes();
			break;
			case 5: oneCan();
			break;
			case 6: both();


			break;
			case 7: sloped();
			break;
			case 8: ToucanEasy();
			break;

			case 9: ToucanHard();
			break;
		}
	}
	bool closeArms(double duration, double speed){
		bool done= false;
			if (time->Get()<duration){
				twocan->SetSpeed(speed);


				}
			else{
				twocan->SetSpeed(0.0);

				done= true;}
			return done;}
	void ToucanHard(){


		bool done= false;
		if (step==1)
			done= driveDistance(100,.85);//distance not known
		else if (step==2)
			done= driveDistance(20, .6); //distance not known
		else if (step==3)
			done= liftArms(.5, 1.0); // check to see if cans are hooked
		else if (step==4)
			done= driveDistance(20, -.5); //distance not known
		else if (step==5){
			done = driveDistance(150,.85); //distance not known
			closeArms(3.0,1.0);}

		else if (step==6)
			done= turn(true);
		else if (step==7)
			done= driveDistance(42, -.75); //distance not known
		else if (step==8)
			done= turn(true);
		else if (step==9)
			done= liftArms(1.6,-1.0);//time not known
		else if (step==10)
			done= driveDistance(18, -.8); //distance not known
		else if (step==11)
			done= liftArms(.5, 1.0); //distance not known*/
		else
			doNothing();
		nextStep(done);}
	void both(){
		bool done= false;
	 if (step==1)
			done = turn(true);
		else if (step==2)
			done= driveDistance(126,.6);
		else if (step==3)
			done= turn(true);
		else
			doNothing();
		nextStep(done);}
	void twoTotes(){


		bool done= false;
		if (step==1)
			done= driveDistance(22.0,.5);
		else if (step==2)
			done= liftArms(1.4,-.75);


		else if (step==3)
			done= driveDistance(36.0,-.6);
		else if (step==4)
			done= driveDistance(24.0, -.5);
		else if (step==5)
			done= liftArms(1.4, .75);
		else if (step==6)

			done= driveDistance(16.0, -.45);
		else if (step==7)
			done= turn(true);
		else
			doNothing();


		nextStep(done);}
	bool liftArms(double duration, double speed){
		bool done= false;
		if (time->Get()<duration){
			jag1->SetSpeed(speed);


			jag2->SetSpeed(speed);
			}
		else{
			jag1->SetSpeed(0.0);
			jag2->SetSpeed(0.0);
			done= true;}
		return done;}
	bool turn(bool isRight){

		SmartDashboard::PutNumber("AngleAuto", sandwich->GetAngle());
		bool done= false;
		//double inches= 22.0;
		//double leftDis= leftEncoder->GetDistance()-leftStart;
		//double rightDis= rightEncoder->GetDistance()-rightStart;
		//if (leftDis<inches && leftDis>-inches && rightDis<inches && rightDis>-inches)
		if (sandwich->GetAngle()<75 && isRight)

			Drive->Turn(.3,isRight);
		else if (sandwich->GetAngle()>-90 && !isRight)
			Drive->Turn(.3,isRight);
		else{
			Drive->DriveSet(0.0,0.0);
			done=true;}
		return done;}

	void ToucanEasy(){


			bool done= false;
			if (step==1)
				done= driveDistance(100,.85);//distance not known
			else if (step==2)
				done= driveDistance(20, .6); //distance not known
			else if (step==3)
				done= liftArms(.5, 1.0); // check to see if cans are hooked
			else if (step==4)
				done= driveDistance(20, -.5); //distance not known
			else if (step==5){
				done = driveDistance(150,.85); //distance not known

				 closeArms(1.0,1.0);}
			else if (step==6)
				done= turn(false);
			else if (step==7)
				done= driveDistance(42, -.75); //distance not known
			else if (step==8)
				done= turn(false);
			else if (step==9)
				done= liftArms(1.6,-1.0);//time not known
			else if (step==10)
				done= driveDistance(18, -.8); //distance not known
			else if (step==11)
				done= liftArms(.5, 1.0); //distance not known*/
			else
				doNothing();
			nextStep(done);}
	void nextStep(bool done){
		if (done){
			step++;
			time->Reset();
			sandwich->Reset();
			leftStart=leftEncoder->GetDistance();


			rightStart= rightEncoder->GetDistance();}}
	void oneCan(){
		bool done= false;
		if (step==1)
			done= driveDistance(9,-.5);
		else if (step==2){
			Drive->DriveSet(0.0,0.0);


			done =liftArms(3.0,-1.0);}
		else if (step==3)
			done= driveDistance(9,-.5);
		else if (step==4){
			done= liftArms(3.0,1.0);


			Drive->DriveSet(0.0,0.0);}
		else if (step==5)
			done= driveDistance(36.0,.75);
		else if (step==6)
			done= driveDistance(25.0,.5);


		else if (step==7)
			done= driveDistance(28.0,.45);
		else


			doNothing();
		nextStep(done);}
	void sloped(){
	bool done= false;
	if (step==1)
		done= driveDistance(11, -.5);
	else if (step==2){
		Drive->DriveSet(0.0,0.0);


		done =liftArms(2.7,-1.0);}
	else if (step==3)
		done= driveDistance(8,-.5);
	else if (step==4){
		done= liftArms(2.5,1.0);


		Drive->DriveSet(0.0,0.0);}
	else if (step==5)
		done= driveDistance(52.0,.75);
	else if (step==6)
		done= driveDistance(10,.5);


	else if (step==7)
		done= driveDistance(5,.5);

	else

		doNothing();
	nextStep(done);
	}
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

	void longArms(){


		bool done= false;
		if (step==1)
			done= driveDistance(100,.85);//distance not known
		else if (step==2)
			done= driveDistance(20, .6); //distance not known
		else if (step==3)
			done= liftArms(.5, 1.0); // check to see if cans are hooked
		else if (step==4)
			done= driveDistance(20, -.5); //distance not known
		else if (step==5)
			done = driveDistance(150,.85); //distance not known
		/*else if (step==6)
			done= turn(false);
		else if (step==7)
			done= driveDistance(42, -.75); //distance not known
		else if (step==8)
			done= turn(false);
		else if (step==9)
			done= liftArms(1.6,-1.0);//time not known
		else if (step==10)
			done= driveDistance(18, -.8); //distance not known
		else if (step==11)
			done= liftArms(.5, 1.0); //distance not known*/
		else
			doNothing();
		nextStep(done);}


	void oneTote(){


		bool done= false;
		if (step==1)
			done= liftArms(1.0,-.75);
		else if (step==2){
			done = driveDistance(50, -.75);
			jag1->SetSpeed(0.0);
			jag2->SetSpeed(0.0);
			}

		else if (step==3)
			done = driveDistance(25, -.5);
		else if (step==4)
			done = driveDistance(46, -.4);
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
		SmartDashboard::PutNumber("x", stick->GetX());
		SmartDashboard::PutNumber("y", stick->GetY());
		SmartDashboard::PutNumber("z", stick->GetTwist());

		if (lifterSpeed < 0) lifterRatio *= -1.0;
		lifterSpeed = lifterSpeed * lifterSpeed * lifterRatio;
		if (xbox->GetRawAxis(5) >= 0.1){
			jag1->SetSpeed(lifterSpeed);
			jag2->SetSpeed(lifterSpeed);
			}

		else if (xbox->GetRawAxis(5) <= -0.1){
			jag1->SetSpeed(lifterSpeed);

			jag2->SetSpeed(lifterSpeed);
			}
		else{
			jag1->SetSpeed(0.0);

			jag2->SetSpeed(0.0);
			}

		if (xbox->GetRawButton(1)){
			twocan->SetSpeed(1.0);
		}
		else if (xbox->GetRawButton(2)){
			twocan->SetSpeed(-1.0);
		}
		else
			twocan->SetSpeed(0);

		Drive->DriveOriented();
		}
	void TestPeriodic(){
		lw->Run();}
	};
START_ROBOT_CLASS(Robot);
