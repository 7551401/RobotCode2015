#include "WPILib.h"
#include "DriveTrain.h"


class Robot: public IterativeRobot
{
private:
	Encoder *encoder;
	LiveWindow *lw; //references LiveWindow class

	Joystick *stick; //references Joystick class; stick used for forward and backward movement
	Joystick *RotStick; //references Joystick class; RotStick used for twisting the stick
	DoubleSolenoid *Sol; //references DoubleSolenoid class
	DriveTrain * Drive;
	Compressor *comp;
	JoystickButton *button1;
	JoystickButton *button2;
	JoystickButton *button3;
	Timer *timer;
	int i=0;
	double y=0;
	double total=0.0;
	//AxisCamera *camera;
	//Image *frame;
	AnalogInput *input;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		Drive = new DriveTrain();

		std::string str= "192.168.0.90";
		//camera= new AxisCamera(str);
		//frame= imaqCreateImage(IMAQ_IMAGE_RGB,0);


		CameraServer::GetInstance()->SetQuality(50);
				//the camera name (ex "cam0") can be found through the roborio web interface
				CameraServer::GetInstance()->StartAutomaticCapture("cam0");




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


		input= new AnalogInput(0);

	}

	void AutonomousInit()
	{
		timer->Start();
	}

	void AutonomousPeriodic()
	{
		double voltage= input->GetVoltage();
		double dis= voltage*1000;
		dis/=9.766;
		dis/=12;
		SmartDashboard::PutNumber("voltage", voltage);
		i+=1;
		total= total+ dis;
		if (i%10==0){
			total/=10;
			SmartDashboard::PutNumber("Feet Away", dis);
			total=0;
				}
		if ((dis)<=0.5)	{
			Drive->DriveAuto();
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		SmartDashboard::PutNumber("Total Distance", encoder->GetDistance());
		SmartDashboard::PutNumber("Distance per Second", encoder->GetRate());
		//SmartDashboard::PutNumber("Color Value: ", camera->GetColorLevel());
		//SmartDashboard::PutNumber("Brightness: ", camera->GetBrightness());

		//Solenoid Code
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

	}

	void TestPeriodic()
	{
		lw->Run(); //Runs LiveWindow
	}
};

START_ROBOT_CLASS(Robot);
