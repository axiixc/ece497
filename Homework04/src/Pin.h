#ifndef Pin_h
#define Pin_h

#include <string>
#include "GPIO.h"

using namespace std;

namespace ECE {

class Pin : public GPIO {
public:
    typedef enum {
        DirectionOut = 0,
        DirectionIn = 1
    } Direction;

    typedef enum {
        ValueHigh = 1,
        ValueLow = 0
    } Value;

    Pin(unsigned);
    Pin(unsigned, Direction);

    inline unsigned pinID() { return m_pinID; };

    Direction direction();
    void setDirection(Direction direction);

    Value value();
    void setValue(Value value);
    void toggleValue();

private:
    unsigned m_pinID;
};

inline Pin::Direction operator!(Pin::Direction direction)
{
    return (direction == Pin::DirectionIn) ?
    Pin::DirectionOut : Pin::DirectionIn;
}

inline Pin::Value operator!(Pin::Value value)
{
    return (value == Pin::ValueHigh) ?
    Pin::ValueLow : Pin::ValueHigh;
}

inline void Pin::toggleValue()
{
    return setValue(!value());
}

}; /* namespace ECE */

#endif /* Pin_h */
