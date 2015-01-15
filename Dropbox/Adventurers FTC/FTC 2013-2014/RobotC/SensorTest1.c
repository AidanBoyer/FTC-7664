#pragma config(Sensor, S2,     ,               sensorI2CHiTechnicColor)

task main(){
	int x;
	while(true){
		x=SensorValue[S2];
		writeDebugStreamLine("Sensor value is %i", x);

	}
}
