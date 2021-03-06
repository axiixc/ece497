#include "Motor.h"
#include "AnalogInput.h"
#include <cfloat>
#include <unistd.h>

using namespace ECE;
void targetIR()
{
    Motor &motor = *new Motor(30, 31, 48, 51);
    AnalogInput &read0 = *new AnalogInput(0);
    AnalogInput &read1 = *new AnalogInput(1);
    
    float min = FLT_MAX;
    int minIndex = 0;
    int i;
    for (i = 0; i < 40; ++i) {
    	
    	int rightValue = read0.value();
    	usleep(10000);
    	int leftValue = read1.value();
    	
    	float lightLevel = (rightValue + leftValue) / 2;
    	if(lightLevel < min) {
    		min = lightLevel;
    		minIndex = i;
    	}
        motor.rotate(Motor::Clockwise);
     }

    for (; i >= minIndex; --i) {
        motor.rotate(Motor::Anticlockwise);
	}
	
    motor.kill();
    
    fprintf(stderr, "Lowest light level(%.f) at: %u\n", min, minIndex);
}

void houndIR(int mode, int deadzone)
{
	Motor &motor = *new Motor(30, 31, 48, 51);
    AnalogInput &read0 = *new AnalogInput((!mode) ? 0 : 1);
    AnalogInput &read1 = *new AnalogInput((!mode) ? 1 : 0);
    while(1) {
    	int rightValue = read0.value();
    	usleep(10000);
    	int leftValue = read1.value();
    	//fprintf(stderr, "Right: %d, Left: %d\n", rightValue, leftValue);
    	if(abs(rightValue - leftValue) < deadzone) {
    		usleep(50000);
    		continue;
    	}
    	else if(rightValue > leftValue) motor.rotate(Motor::Clockwise);
    	else motor.rotate(Motor::Anticlockwise);
    }
}
int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Usage:%s <mode> <deadzone range in mV>\n\tMode = 0, track IR\n\tMode = 1, avoid IR\n", argv[0]);
		exit(-1);
	}
    Pin &trigger = *new Pin(3, Pin::DirectionIn);
    AnalogInput::initialize();
    
    while (trigger.value() != Pin::ValueLow);
    targetIR();
    houndIR(atoi(argv[1]), atoi(argv[2]));

    return 0;
}
