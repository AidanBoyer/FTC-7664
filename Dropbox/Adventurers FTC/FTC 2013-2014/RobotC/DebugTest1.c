#include "JoystickDriver.c"
task main()
{
	clearDebugStream();

	//writeDebugStream("this is a test");
	//writeDebugStream("this is a test\n");
	//writeDebugStream("Available space: ", getAvailSpaceInDebugStream());
	//getAvailSpaceInDebugStream();
int x = 0;
while (true)
{
	x++;
	writeDebugStreamLine("The value of x is %i", x);
}
}
