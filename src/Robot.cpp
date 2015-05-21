//Imports necessary files for the program to run
#include "WPILib.h"
#include "DriveTrain.h"
#include "SmartDashboard/SendableChooser.h"
#include "PWM.h"

//This creates the Robot Class and implements an interface called IterativeRobot
//IterativeRobot goes through each "Periodic" method and calls it every few milliseconds
class Robot: public IterativeRobot{
	
//The following variables are instance variables to be used later in the program

private:


	Encoder *leftEncoder; //Pointer to the left Encoder
	Encoder *rightEncoder; //Pointer to the right Encoder
	LiveWindow *lw; //Pointer to the Live Window
	Timer *time; //Pointer to a timer that keeps track of time in seconds
	Joystick *arcadeStick; //Pointer to the arcade drive controller
	Joystick *xbox; //Pointer to the xbox controller
	DriveTrain *Drive; //Pointer to the drive train
	Jaguar *jag1; //Pointer to one of the elevator motors
	Jaguar *jag2; //Pointer to the other elevator motor
	SendableChooser *chooser; //Pointer to the object that allows you to press buttons for each Autonomous program
	int AutoCode; //Pointer to which Auto program is selected
	int step=0; //Pointer to the step in each Auto program
	
	//Initializes variables for each encoder to keep track of how far they have gone
	double leftStart=0.0; 
	double rightStart=0.0;
	
	//Constructor for the Robot Class; initializes and instantiates necessary objects and variables.
	void RobotInit()
	{
		Drive = new DriveTrain(); //Instantiates a DriveTrain object
		arcadeStick = new Joystick(0); //Instantiates a Joystick object in USB port 0
		xbox = new Joystick(1); //Instantiates a Joystick object in USB port 1
		
		//reference WPI Lib for encoder parameters
		leftEncoder = new Encoder (24,25, true, CounterBase:: k4X); //Instantiates an encoder in Ports 24/25
		rightEncoder = new Encoder (16,17, true, CounterBase:: k4X); //Instantiates an encoder in Ports 16/17

		//Tells each encoder to set the predetermined distance for each tick on the encoder
		leftEncoder->SetDistancePerPulse(6.0*3.14/128.0); 
		rightEncoder->SetDistancePerPulse(6.0*3.14/256.0); 
		
		//Instantiates a SendableChooser object
		chooser = new SendableChooser();

		//Adds The different autonomous modes to the SendableChooser
		//Parameters include a string and void therefore needing the (void*) class cast notation
		chooser->AddDefault("Do nothing \n(Set in avoidable area)", (void*)1);
		chooser->AddObject("One can from middle starting on flat\n(Set middle frame on edge of ramp)" , (void*)2);
		chooser->AddObject("One can from middle starting on ramp", (void*)3);
		
		//Adds the auto modes to the SmartDashboard
		SmartDashboard::PutData("Autonomous modes", chooser);
		
		//Resets the Encoders
		leftEncoder->Reset();
		rightEncoder->Reset();
		
		//Instantiates both jaguars in ports 4 and 5
		jag1= new Jaguar(4);
		jag2= new Jaguar(5);
		}
		
		
	//The initializer for the Autonomous modes
	void AutonomousInit()
	{
		
		//Sets the AutoCode to whatever the user selects
		AutoCode = (int)(chooser->GetSelected());
		
		//Creates a timer and starts it
		time= new Timer();
		time->Start();
		
		//Sets the auto code step to 1
		step=1;
		
		//Resets the values of each encoder 
		leftEncoder->Reset();
		rightEncoder->Reset();
		rightStart=0.0;
		leftStart=0.0;
		
	}

	//This is where whatever happens in Auto occurs
	void AutonomousPeriodic()
	{
		
		//A switch statement is used to determine which code is selected
		//If the first case is selected, AutonomousPeriodic() will call the doNothing() program until it is completed
		switch(AutoCode)
		{
			case 1: doNothing(); //Robot Does nothing
			break;
			case 2: oneCan(); //Robot grabs can from middle (starts on ground)
			break;
			case 3: sloped(); //Robot grabs can from middle (starts on ramp)
			break;
		}
	}
	
	//Created method with parameters of a duration and a speed
	//Lifts the elevator arms with the speed for the time alotted
	//returns a boolean value of whether the task has been completed
	bool liftArms(double duration, double speed)
	{
		bool done= false;
		if (time->Get()<duration)
		{
			jag1->SetSpeed(speed);
			jag2->SetSpeed(speed);
		}
		else
		{
			jag1->SetSpeed(0.0);
			jag2->SetSpeed(0.0);
			done= true;
		}
		return done;
		
	}

	//method that takes in a boolean value
	//if an auto step is done this will cause it to move onto the next step and reset values
	void nextStep(bool done)
	{
		if (done)
		{
		  	step++;
			time->Reset();
			leftStart=leftEncoder->GetDistance();
			rightStart= rightEncoder->GetDistance();
		}
	}
	
	//Auto Program that picks up one can
	void oneCan()
	{
		bool done= false; //Initializes that the program is not done
		
		//If the step is 1, drive 9 inches at a speed of negative .5
		if (step==1)
		{
			done= driveDistance(9,-.5);
		}
		
		//If the step is 2, stop driving and lift the arms for 3 seconds at a speed of -1
		else if (step==2)
		{
			Drive->DriveSet(0.0,0.0);
			done =liftArms(3.0,-1.0);
		}
		else if (step==3)
		{
			done= driveDistance(9,-.5);
		}
		else if (step==4)
		{
			done= liftArms(3.0,1.0);
			Drive->DriveSet(0.0,0.0);
		}
		else if (step==5)
		{
			done= driveDistance(36.0,.75);
		}
		else if (step==6)
		{
			done= driveDistance(25.0,.5);
		}
		else if (step==7)
		{
			done= driveDistance(28.0,.45);
		}
		else
		{
			doNothing();
		}
		nextStep(done); //If the step is done move on to the next step
	}
	
	//Auto Program to pick up a can from the middle starting on the ramp
	void sloped()
	{
	bool done= false;
	if (step==1)
	{
		done= driveDistance(11, -.5);
	}
	else if (step==2)
	{
		Drive->DriveSet(0.0,0.0);
		done =liftArms(2.7,-1.0);
	}
	else if (step==3)
	{
		done= driveDistance(8,-.5);
	}
	else if (step==4)
	{
		done= liftArms(2.5,1.0);
		Drive->DriveSet(0.0,0.0);
	}
	else if (step==5)
	{
		done= driveDistance(52.0,.75);
	}
	else if (step==6)
	{
		done= driveDistance(10,.5);
	}
	else if (step==7)
	{
		done= driveDistance(5,.5);
	}
	else
	{
		doNothing();
	}
	nextStep(done);
	}
	
	//Program that causes the Robot to not drive
	void doNothing()
	{
		Drive->DriveSet(0.0,0.0);
	}
	
	//Function that takes in an amount of inches and a predetermined speed
	//Tells the Robot to drive at the speed until the amount of inches has been reached on either of the encoders
	//Returns true when the robot has driven the distance
	bool driveDistance(int inches, double speed)
	{
		bool done = false;
		double leftDis= leftEncoder->GetDistance()-leftStart;
		double rightDis= rightEncoder->GetDistance()-rightStart;
		if (leftDis<inches && leftDis>-inches && rightDis<inches && rightDis>-inches)
		{
			Drive->DriveSet(speed,0.0);
		}
		else
		{
			Drive->DriveSet(0.0,0.0);
			done=true;
		}
		return done;
	}

	//Initializes the Teleoperated mode
	void TeleopInit()
	{
		rightEncoder->Reset();
		leftEncoder->Reset();
	}

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
