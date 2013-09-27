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

void houndIR()
{
	Motor &motor = *new Motor(30, 31, 48, 51);
    AnalogInput &read0 = *new AnalogInput(0);
    AnalogInput &read1 = *new AnalogInput(1);
    while(1) {
    	int rightValue = read0.value();
    	usleep(10000);
    	int leftValue = read1.value();
    	fprintf(stderr, "Right: %d, Left: %d\n", rightValue, leftValue);
    	if(rightValue > leftValue) motor.rotate(Motor::Clockwise);
    	else motor.rotate(Motor::Anticlockwise);
    }
}
int main(int argc, char *argv[])
{
    Pin &trigger = *new Pin(3, Pin::DirectionIn);
    AnalogInput::initialize();
    
    while (trigger.value() != Pin::ValueLow);
    targetIR();
    houndIR();

    return 0;
}
