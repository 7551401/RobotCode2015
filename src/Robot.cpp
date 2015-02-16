#include "WPILib.h"
#include "DriveTrain.h"
#include "SmartDashboard/SendableChooser.h"


class Robot: public IterativeRobot
{
private:
	Encoder *encoder;
	LiveWindow *lw; //references LiveWindow class
	Timer *time;
	Joystick *stick; //references Joystick class; stick used for forward and backward movement
	Joystick *RotStick; //references Joystick class; RotStick used for twisting the stick
	DriveTrain * Drive;
	Joystick *xbox;
	DoubleSolenoid *Sol; //references DoubleSolenoid class
	DoubleSolenoid *Cam2;
	DoubleSolenoid *Cam3;
	DoubleSolenoid *shift;
	Jaguar *jag1;
	Jaguar *jag2;
	Compressor *comp;
	JoystickButton *button1;
	JoystickButton *button2;
	JoystickButton *button3;

	Timer *timer;
	SendableChooser *chooser;
	int Auto1;
	int Auto2;

	JoystickButton *abutton;
	JoystickButton *ybutton;
	Gyro *sandwich;
	AnalogInput *input;
	AnalogInput *input2;
	Servo *servo;
	double y=0.0;


	void RobotInit()
	{
		lw = LiveWindow::GetInstance();

		//std::string str= "192.168.0.90";
		Drive = new DriveTrain();




		xbox= new Joystick(1); //input tbd



		//stick= new Joystick(0);
		stick = new Joystick(0); //Creates a new Joystick for forward and backward movement
		comp= new Compressor(); //Creates a new Compressor to Compress air
		comp->Start(); //Starts Compressor
		/*Sol= new DoubleSolenoid(0,0,1); //Creates a new DoubleSolenoid with parameters of 0 for the port
		Cam2= new DoubleSolenoid(1,0,1);
		Cam3= new DoubleSolenoid(2,0,1);*/

		shift = new DoubleSolenoid(6,7);

		/*Sol->Set(DoubleSolenoid::Value::kForward); //Set DoubleSolenoid to go forward
		Cam2->Set(DoubleSolenoid::Value::kForward);
		Cam3->Set(DoubleSolenoid::Value::kForward);
		shift->Set(DoubleSolenoid::Value::kForward);*/
		encoder = new Encoder (18, 19, true, CounterBase:: k4X);
		/*servo = new Servo (0);

		button1= new JoystickButton(stick,1);
		button2= new JoystickButton(stick,2);
		button3= new JoystickButton(stick,3);
		Auto1 = 1;
		Auto2 = 2;
		//Multiple autonomous programs
		chooser = new SendableChooser();
		chooser->AddDefault("Autonomous 1", &Auto1);
		chooser->AddObject("Autonomous 2", &Auto2);
		SmartDashboard::PutData("Autonomous modes", chooser);




		abutton= new JoystickButton(xbox,1); //input tbd
		ybutton= new JoystickButton(xbox,4); //input tbd


		input= new AnalogInput(0);
		input2= new AnalogInput(1);
		sandwich= new Gyro(input2);
		sandwich->InitGyro();
		sandwich->Reset();
		 */
		jag1= new Jaguar(4);
		jag2= new Jaguar(5);
	}

	void Grab(){
		Cam2->Set(DoubleSolenoid::kReverse);
		Cam3->Set(DoubleSolenoid::kReverse);
	}

	void LetGo(){
		Cam2->Set(DoubleSolenoid::kReverse);
		Cam3->Set(DoubleSolenoid::kReverse);
	}

	void Push(){
		Sol->Set(DoubleSolenoid::kReverse);
	}

	void donePush(){
		Sol->Set(DoubleSolenoid::kForward);
	}

	void AutonomousInit()
	{

		//int AutoCode = *(int*)(chooser->GetSelected());

		time= new Timer();
		time->Start();
		y=0;

	}

	void AutonomousPeriodic()
	{

	/*	double zeTime= time->Get();
		//double voltage= input->GetVoltage();
		// dis= voltage*1000;
		//dis/=9.766;
		//dis/=12;
		//y=y+(.01*(dis-y));
		//picks up right bin
		if(zeTime<=1.0){
			//Grab();//time not known
			Drive->DriveSet(0.0,0.0);
			jag1->SetSpeed(1.0); //speed not known
			jag2->SetSpeed(1.0);//speed not known not known
			;}
		//drives right to tote
		else if (zeTime<=2.0 && y>=.2){ //time and distance not known
			Drive->DriveAuto(); //speed not known
		}
		//picks up right tote and left bin
		else if (zeTime<=3.0){
			//LetGo();//time not known
			jag1->SetSpeed(-0.8);//speed not known
			jag2->SetSpeed(-0.8);
			Drive->DriveSet(0.0,0.0);}// speed not known

		else if (zeTime<=5.0){
			//Grab();
			Drive->DriveSet(0.0,0.0);
		}
		else if (zeTime<=6.0){//time not known
			Drive->DriveSet(1.0, 0.3);//speed and direction not known
		}
		else if (zeTime<=7.0){//time not known
			jag1->SetSpeed(0.9);//speed not known
			jag2->SetSpeed(0.9); //speed not known
			Drive->DriveSet(0.0,0.0);
		}
		else if (zeTime<=7.5){//time not known
			Drive->DriveAuto();
		}
		else if (zeTime<=8.5){//time not known
			//LetGo();
			//Push();
			jag1->SetSpeed(-1.0);//speed not known
			jag2->SetSpeed(-1.0);//speed not known
			Drive->DriveSet(0.0,0.0);
		}
		else if (zeTime<=8.75){
			//donePush();
			Drive->DriveSet(-1.0, 0.0);
		}
		else{
			Drive->DriveSet(0.0,0.0);
		}*/

	}

	void TeleopInit()
	{
		y=0;
	}

	void TeleopPeriodic()
	{

		SmartDashboard::PutNumber("Total Distance", encoder->GetDistance());
		SmartDashboard::PutNumber("Distance per Second", encoder->GetRate());

		/*
		if (stick->GetRawButton(5)) {
			Sol->Set(DoubleSolenoid::kForward);
		}
		if (stick->GetRawButton(6)) {
					Sol->Set(DoubleSolenoid::kReverse);
				}
		if (stick->GetRawButton(3)){
			LetGo();
		}
		if (stick->GetRawButton(4)){
			Grab();
				}
		if (stick->GetRawButton(2)){
			shift->Set(DoubleSolenoid::kReverse);
		}
		if (stick->GetRawButton(1)){
			shift->Set(DoubleSolenoid::kForward);
		}

		//camera->GetImage(frame);
		//imaqDrawShapeOnImage(frame,frame, {10,10,100,100}, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL,0.0f);
		//CameraServer::GetInstance()->SetImage(frame);
		//camera->GetImage(frame);
		//imaqDrawShapeOnImage(frame,frame, {10,10,100,100}, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL,0.0f);
		//CameraServer::GetInstance()->SetImage(frame);
		double voltage= input->GetVoltage();
		double dis= voltage*1000;
		dis/=9.766;
		dis/=12;
		SmartDashboard::PutNumber("voltage", voltage);
		y=y+(.01*(dis-y));
		SmartDashboard::PutNumber("Feet Away: ", y); */

		float lifterSpeed = xbox->GetRawAxis(5);
		float lifterRatio = -0.75;
		lifterSpeed = lifterSpeed * lifterSpeed *lifterSpeed * lifterRatio;
		if (xbox->GetRawAxis(5) >= 0.2){
			jag1->SetSpeed(lifterSpeed);
			jag2->SetSpeed(lifterSpeed);
		}
		else if (xbox->GetRawAxis(5) <= -0.2){
			jag1->SetSpeed(lifterSpeed);
			jag2->SetSpeed(lifterSpeed);
		}
		else{
			jag1->SetSpeed(0.0);
			jag2->SetSpeed(0.0);
		}


		//Double Solenoid Code
		if (stick->GetRawButton(3)) {
			shift->Set(DoubleSolenoid::kForward);
		};

		if (stick->GetRawButton(4)) {
			shift->Set(DoubleSolenoid::kReverse);
		};


		Drive->DriveOriented();

	}

	void TestPeriodic()
	{
		lw->Run(); //Runs LiveWindow
	}


};

START_ROBOT_CLASS(Robot);
