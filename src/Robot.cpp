#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	RobotDrive *myRobot;
	Joystick *stick;
	Joystick *RotStick;
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		myRobot= new RobotDrive(3,2,1,0);/*possibly make two objects:
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
		stick = new Joystick (0,Joystick::kDefaultYAxis,0);
		RotStick= new Joystick (0,Joystick::kDefaultTwistAxis, 0);



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
		myRobot->ArcadeDrive(stick, Joystick::kDefaultYAxis, RotStick, Joystick::kDefaultTwistAxis, true );

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
