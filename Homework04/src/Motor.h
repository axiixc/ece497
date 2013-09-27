#ifndef Motor_h
#define Motor_h

#include "Pin.h"
#include <vector>

using namespace std;

namespace ECE {

class Motor {
public:
    Motor(unsigned pin0, unsigned pin1, unsigned pin2, unsigned pin3);

    typedef enum {
        Clockwise,
        Anticlockwise,
    } Direction;

    void rotate(Direction);
    void kill();

private:
    void writePins(const Pin::Value *values);

    Pin &m_pin0;
    Pin &m_pin1;
    Pin &m_pin2;
    Pin &m_pin3;

    unsigned m_valuesIdx;
};

}

#endif /* Motor_h */