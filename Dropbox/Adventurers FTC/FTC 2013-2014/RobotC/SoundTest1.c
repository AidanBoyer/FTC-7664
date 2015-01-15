#include "joystickDriver.c";

const int frequency = 1000;
const int durationInMsecs = 1000;
const int durationIn10MsecTicks = durationInMsecs / 10;

task main()
{
	PlayTone(frequency, durationIn10MsecTicks);
	wait10Msec(durationIn10MsecTicks);
}
