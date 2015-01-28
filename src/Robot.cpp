#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	Encoder *encoder;
	LiveWindow *lw; //references LiveWindow class
	RobotDrive *myRobot; //references RobotDrive class
	Joystick *stick; //references Joystick class; stick used for forward and backward movement
	Joystick *RotStick; //references Joystick class; RotStick used for twisting the stick
	DoubleSolenoid *Sol; //references DoubleSolenoid class
	Victor *vic1;
	Victor *vic2;
	Victor *vic3;
	Victor *vic4;
	Compressor *comp;
	JoystickButton *button1;
	JoystickButton *button2;
	JoystickButton *button3;
	Timer *timer;
	AxisCamera *camera;
	Image *frame;
	double getThrottle(double val){
	 float throttle = stick->GetThrottle();
	 throttle++;
	 throttle = throttle *((1-val)/2);
	 throttle+= val;
	 return throttle;

	}
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		vic1 = new Victor(3);
		vic2= new Victor(2);
		vic3= new Victor(1);
		vic4= new Victor(0);
		myRobot= new RobotDrive(vic1,vic2,vic3,vic4);
		std::string str= "192.168.0.90";
		camera= new AxisCamera(str);
		frame= imaqCreateImage(IMAQ_IMAGE_RGB,0);





		//Motors are inverted because the motors were initially messed up
		myRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
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



	}

	void AutonomousInit()
	{
		timer->Start();
	}

	void AutonomousPeriodic()
	{
		if (timer->Get()<=4){
			myRobot->ArcadeDrive(1.0,0.0, true);
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{


		float throttle = getThrottle(.5);
		myRobot->ArcadeDrive(stick->GetY()*throttle, stick->GetTwist()*throttle, true); //Scales the Joystick values by the throttle value
		SmartDashboard::PutNumber("Total Distance", encoder->GetDistance());
		SmartDashboard::PutNumber("Distance per Second", encoder->GetRate());
		SmartDashboard::PutNumber("Color Value: ", camera->GetColorLevel());
		SmartDashboard::PutNumber("Brightness: ", camera->GetBrightness());
		if (stick->GetRawButton(5)) {
			Sol->Set(DoubleSolenoid::kForward);
		}
		if (stick->GetRawButton(6)) {
					Sol->Set(DoubleSolenoid::kReverse);
				}
		camera->GetImage(frame);
		imaqDrawShapeOnImage(frame,frame, {10,10,100,100}, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL,0.0f);
		CameraServer::GetInstance()->SetImage(frame);


	}

	void TestPeriodic()
	{
		lw->Run(); //Runs LiveWindow
	}
};

START_ROBOT_CLASS(Robot);
