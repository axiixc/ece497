#include "Motor.h"

using namespace ECE;

void do360()
{
    Motor &motor = *new Motor(30, 31, 48, 51);

    for (unsigned i = 0; i < 40; ++i)
        motor.rotate(Motor::Clockwise);

    for (unsigned i = 0; i < 40; ++i)
        motor.rotate(Motor::Anticlockwise);

    motor.kill();
}

int main(int argc, char *argv[])
{
    Pin &trigger = *new Pin(3, Pin::DirectionIn);

    for (;;)
    {
        while (trigger.value() != Pin::ValueLow);
        do360();
    }

    return 0;
}
