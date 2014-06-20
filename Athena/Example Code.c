#pragma config(Motor,  port2,           backleft,      tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port3,           backright,     tmotorVex269, openLoop)
#pragma config(Motor,  port4,           Claw,          tmotorVex269, openLoop)
#pragma config(Motor,  port8,           frontright,    tmotorVex269, openLoop)
#pragma config(Motor,  port9,           frontleft,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port10,          lift,          tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////
void driveArcade(int y, int x)
{
	motor[frontleft] = motor[backleft] = y - x;
	motor[frontright] = motor[backright] = y + x;
}

void clawcontrol(int a)
{
	motor[Claw] = a;
}

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
	motor[port2] = 127;
motor[port3] = motor[port2];
wait1Msec(1000);
motor[port8] = 127;
wait1Msec(1000);
motor[port9]=127;
wait1Msec(1000);
motor[backleft]=0;
motor[backright]=0;
motor[frontleft]=0;
motor[frontright]=0;

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	driveArcade(100,0);
wait10Msec(100);

	clawcontrol(100);
	driveArcade(0,0);
wait1Msec(100);

	driveArcade(-50,0);
wait10Msec(50);

	driveArcade(0,0);
//***************************************************************

	while (true)
	{
		int driveX = vexRT[Ch1];
		int driveY = vexRT[Ch2];

if (abs(driveY) < 5) driveY = 0; // Deadband
			if (abs(driveX) < 5) driveX = 0;
	driveArcade(driveY, -driveX);


	int claw = vexRT[Ch3]; //CLAW
		if (abs(claw) < 5) claw = 0; // Deadband
	clawcontrol(claw);

	if (vexRT[Btn6U] == 1)
	{
			motor[lift]=127;
	}
	 if (vexRT[Btn6D] == 1)
	{
			motor[lift]=-127;
	}
	else
	{
		if (vexRT[Btn6U] != 1)
				motor[lift]=0;
	}
	}
}
