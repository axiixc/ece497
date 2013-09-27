#include "Motor.h"
#include "AnalogInput.h"
#include <cfloat>

using namespace ECE;
void do360()
{
    Motor &motor = *new Motor(30, 31, 48, 51);
    AnalogInput &read0 = *new AnalogInput(0);
    AnalogInput &read1 = *new AnalogInput(1);
    
    float min = FLT_MAX;
    int minIndex = 0;
    int i;
    for (i = 0; i < 40; ++i) {
    	float lightLevel = (read0.value() + read1.value()) / 2;
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

int main(int argc, char *argv[])
{
    Pin &trigger = *new Pin(3, Pin::DirectionIn);
    
    AnalogInput::initialize();
    for (;;)
    {
        while (trigger.value() != Pin::ValueLow);
        do360();
    }

    return 0;
}
