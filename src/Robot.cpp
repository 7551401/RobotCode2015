#include "WPILib.h"
#include "DriveTrain.h"

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
	Victor *vic5;
	Victor *vic6;
	Compressor *comp;
	JoystickButton *button1;
	JoystickButton *button2;
	JoystickButton *button3;
	JoystickButton *abutton;
	JoystickButton *ybutton;
	Gyro *sandwich;

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
		Sol= new DoubleSolenoid(0,0,1); //Creates a new DoubleSolenoid with parameters of 0 for the port

		Sol->Set(DoubleSolenoid::Value::kForward); //Set DoubleSolenoid to go forward
		encoder = new Encoder (18, 19, true, CounterBase:: k4X);

		button1= new JoystickButton(stick,1);
		button2= new JoystickButton(stick,2);
		button3= new JoystickButton(stick,3);
		abutton= new JoystickButton(xbox,1); //input tbd
		ybutton= new JoystickButton(xbox,4); //input tbd


		input2= new AnalogInput(1);
		sandwich= new Gyro(input2);
		sandwich->InitGyro();
		sandwich->Reset();
	}

	void AutonomousInit()
	{
		time= new Timer();
		time->Start();
		y=0;
	}

	void AutonomousPeriodic()
	{
		double zeTime= time->Get();
		double voltage= input->GetVoltage();
		double dis= voltage*1000;
		dis/=9.766;
		dis/=12;
		y=y+(.01*(dis-y));
		//picks up right bin
		if(zeTime<=1.0){ //time not known
			vic5->SetSpeed(1.0); //speed not known
			vic6->SetSpeed(1.0);} //speed not known not known
		//drives right to tote
		else if (zeTime<=2.0 && y>=.2){ //time and distance not known
			myRobot->ArcadeDrive(1.0,0.0,true); //speed not known
		}
		//picks up right tote and left bin
		else if (zeTime<=3.0){//time not known
			vic5->SetSpeed(-0.8);//speed not known
			vic6->SetSpeed(-0.8);}// speed not known
		else if (zeTime<=6.0){//time not known
			myRobot->ArcadeDrive(1.0, 0.3,true);//speed and direction not known
		}
		else if (zeTime<=7.0){//time not known
			vic5->SetSpeed(0.9);//speed not known
			vic6->SetSpeed(0.9); //speed not known
		}
		else if (zeTime<=7.5){//time not known
			myRobot->ArcadeDrive(1.0,0.0,true);
		}
		else if (zeTime<=8.5){//time not known
			vic5->SetSpeed(-1.0);//speed not known
			vic6->SetSpeed(-1.0);//speed not known
		}
		else if (zeTime<=8.75){
			myRobot->ArcadeDrive(-1.0, 0.0,true);
		}
		else{
			myRobot->ArcadeDrive(0.0,0.0,true);
		}
	}

	void TeleopInit()
	{
		y=0;
	}

	void TeleopPeriodic()
	{

		SmartDashboard::PutNumber("Total Distance", encoder->GetDistance());
		SmartDashboard::PutNumber("Distance per Second", encoder->GetRate());
		if (stick->GetRawButton(5)) {
			Sol->Set(DoubleSolenoid::kForward);
		}
		if (stick->GetRawButton(6)) {
					Sol->Set(DoubleSolenoid::kReverse);
				}
		//camera->GetImage(frame);
		//imaqDrawShapeOnImage(frame,frame, {10,10,100,100}, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL,0.0f);
		//CameraServer::GetInstance()->SetImage(frame);
		double voltage= input->GetVoltage();
		double dis= voltage*1000;
		dis/=9.766;
		dis/=12;
		SmartDashboard::PutNumber("voltage", voltage);
		y=y+(.01*(dis-y));
		SmartDashboard::PutNumber("Feet Away: ", y);
		total=0;
		if (xbox->GetRawButton(1)){
			vic5->SetSpeed(1.0);
			vic6->SetSpeed(1.0);
		}
		else if (xbox->GetRawButton(4)){
			vic5->SetSpeed(-1.0);
			vic6->SetSpeed(-1.0);
	}
		else{
			vic5->SetSpeed(0.0);
			vic6->SetSpeed(0.0);
		}


	}

	void TestPeriodic()
	{
		lw->Run(); //Runs LiveWindow
	}
};

START_ROBOT_CLASS(Robot);
