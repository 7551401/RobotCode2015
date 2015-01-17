#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	RobotDrive *myRobot;
	Joystick *stick;
	Joystick *RotStick;
	DoubleSolenoid *Sol;
	Victor *vic1;
	Victor *vic2;
	Victor *vic3;
	Victor *vic4;
	Compressor *comp;
	JoystickButton *button1;
	JoystickButton *button2;
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		vic1 = new Victor(3);
		vic2= new Victor(2);
		vic3= new Victor(1);
		vic4= new Victor(0);
		myRobot= new RobotDrive(vic1,vic2,vic3,vic4);/*possibly make two objects:
		a left and right robot for each analog stick on an x-box controller?
		This would allow for the sticks to be used in opposite directions and
		be able to avoid a GetTwist() method.
		*/

		//stick1= new Joystick(0);
		//stick2= new Joystick(1);
		//myRobot= new RobotDrive(3,2,1,0);



		//Motors are inverted because the motors were initially messed up
		myRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		//stick= new Joystick(0);
		stick = new Joystick(0);
		comp= new Compressor();
		comp->Start();
		Sol= new DoubleSolenoid(0,0,0);
		bool isPressed= false;
		Sol->Set(DoubleSolenoid::Value::kForward);

		button1= new JoystickButton(stick,1);
		button2= new JoystickButton(stick,2);




	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		//myRobot->ArcadeDrive(stick, Joystick::kDefaultYAxis, stick, Joystick::kDefaultTwistAxis, true);
		//myRobot->Drive(ThroStick->GetThrottle(), ThroStick->GetThrottle());
		//vic1->Set((((ThroStick->GetThrottle()+1)*.4)+.2),0);
		//vic2->Set((((ThroStick->GetThrottle()+1)*.4)+.2),0);
		//vic3->Set((((ThroStick->GetThrottle()+1)*.4)+.2),0);
		//vic4->Set((((ThroStick->GetThrottle()+1)*.4)+.2),0);


		//float throttle = (((stick->GetThrottle()+1)*0.4)+.2);
		//float magnitude=stick->GetMagnitude();
		/*if (magnitude<0.08){
			magnitude=0;*/
		//}
		//float direction= RotStick->GetTwist();
		//if (direction<.2 && direction>-.2){
			//direction=0;
		//}
		//direction*=.75;
		float throttle = stick->GetThrottle();
		throttle = ((throttle+1) *.25) + .5;
		myRobot->ArcadeDrive(stick->GetY()*throttle, stick->GetTwist()*throttle, true);
		//SmartDashboard::PutNumber("Mag:", magnitude);
		//SmartDashboard::PutNumber("Dir:", direction);
		//SmartDashboard::PutNumber("RotStick->DirectionDegrees", RotStick->GetTwist());
		//SmartDashboard::PutNumber("stick->DirectionDegrees", stick->GetDirectionDegrees());
		//SmartDashboard::PutNumber("RotStick->GetMag",RotStick->GetMagnitude());



	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
