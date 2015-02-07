#include "WPILib.h"
#include "DriveTrain.h"

class Robot: public IterativeRobot
{
private:
	Encoder *encoder;
	LiveWindow *lw; //references LiveWindow class
	Joystick *stick; //references Joystick class; stick used for forward and backward movement
	Joystick *RotStick; //references Joystick class; RotStick used for twisting the stick
	DriveTrain * Drive;
	DoubleSolenoid *Sol; //references DoubleSolenoid class
	Compressor *comp;
	JoystickButton *button1;
	JoystickButton *button2;
	JoystickButton *button3;
	Timer *timer;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		std::string str= "192.168.0.90";
		Drive = new DriveTrain();





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
		}
	}

	void TeleopInit()
	{

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


	}

	void TestPeriodic()
	{
		lw->Run(); //Runs LiveWindow
	}
};

START_ROBOT_CLASS(Robot);
