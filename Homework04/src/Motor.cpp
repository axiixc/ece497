#include "Motor.h"
#include <algorithm>
#include <unistd.h>

using namespace ECE;

static const Pin::Value Values[8][4] = {
    { Pin::ValueHigh, Pin::ValueLow, Pin::ValueLow, Pin::ValueLow },
    { Pin::ValueHigh, Pin::ValueHigh, Pin::ValueLow, Pin::ValueLow },
    { Pin::ValueLow, Pin::ValueHigh, Pin::ValueLow, Pin::ValueLow },
    { Pin::ValueLow, Pin::ValueHigh, Pin::ValueHigh, Pin::ValueLow },
    { Pin::ValueLow, Pin::ValueLow, Pin::ValueHigh, Pin::ValueLow },
    { Pin::ValueLow, Pin::ValueLow, Pin::ValueHigh, Pin::ValueHigh },
    { Pin::ValueLow, Pin::ValueLow, Pin::ValueLow, Pin::ValueHigh },
    { Pin::ValueHigh, Pin::ValueLow, Pin::ValueLow, Pin::ValueHigh },
};
static const unsigned NumberOfValues = sizeof(Values) / sizeof(Values[0]);

Motor::Motor(unsigned pin0, unsigned pin1, unsigned pin2, unsigned pin3)
: m_pin0(*new Pin(pin0, Pin::DirectionOut))
, m_pin1(*new Pin(pin1, Pin::DirectionOut))
, m_pin2(*new Pin(pin2, Pin::DirectionOut))
, m_pin3(*new Pin(pin3, Pin::DirectionOut))
, m_valuesIdx(0)
{
}

void Motor::rotate(Direction direction)
{
    writePins(Values[m_valuesIdx]);

    unsigned delta = (direction == Clockwise) ? 1 : NumberOfValues - 1;
    m_valuesIdx = (m_valuesIdx + delta) % NumberOfValues;
}

void Motor::kill()
{
    static const Pin::Value OffValues[4] = { Pin::ValueLow, Pin::ValueLow, Pin::ValueLow, Pin::ValueLow };
    writePins(OffValues);
}

void Motor::writePins(const Pin::Value *values)
{
    fprintf(stderr, "-> %d %d %d %d\n", values[0], values[1], values[2], values[3]);

    m_pin0.setValue(values[0]);
    m_pin1.setValue(values[1]);
    m_pin2.setValue(values[2]);
    m_pin3.setValue(values[3]);
    usleep(75000);
}
