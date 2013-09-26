//
//  GPIOPin.h
//  libGPIO
//
//  Created by James Savage on 9/16/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef GPIO_Pin_h
#define GPIO_Pin_h

#include <string>

using namespace std;

namespace GPIO {

class Pin {
public:
    typedef enum {
        DirectionOut,
        DirectionIn
    } Direction;

    typedef enum {
        ValueHigh,
        ValueLow
    } Value;

    typedef struct {
        unsigned head_id;

    } Description;

    Pin(unsigned);
    Pin(unsigned, Direction);

    inline unsigned pinID() { return m_pinID; };

    Direction direction();
    void setDirection(Direction direction);

    Value value();
    void setValue(Value value);
    void toggleValue();

private:
    string readPinFile(string filename);
    void writePinFile(string filename, string value);
    
    unsigned m_pinID;
    string m_pinDir;
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

};

#endif /* gpio_pin_h */
