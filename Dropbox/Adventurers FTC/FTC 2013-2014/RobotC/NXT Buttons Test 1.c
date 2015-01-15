#include "joystickDriver.c";

task main()
{
	int count = 0;
	bool countChanged;
	while(true)
	{
		if(nNxtButtonPressed != -1)
		{
			if(nNxtButtonPressed == 1) count++;
			else if(nNxtButtonPressed == 2) count--;
			else if(nNxtButtonPressed == 3) count = 0;
			nxtDisplayCenteredBigTextLine(3, "%i", count);
   	}
   	wait10Msec(10);
   	nxtDisplayCenteredBigTextLine(3, "%i", count);
	}
}
