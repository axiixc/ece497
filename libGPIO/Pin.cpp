//
//  GPIOPin.cpp
//  libGPIO
//
//  Created by James Savage on 9/16/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "pin.h"

#include <fstream>
#include <sstream>

#define GPIO_DIRECTORY "/sys/class/gpio/"
#define GPIO_EXPORT_FILE GPIO_DIRECTORY "export"

using namespace GPIO;

Pin::Pin(unsigned pinID)
: m_pinID(pinID)
{
    stringstream pinDir;
    pinDir << GPIO_DIRECTORY << pinID << "/";
    m_pinDir = pinDir.str();
    
    ifstream dirFile(m_pinDir);
    if (dirFile.good())
    {
        dirFile.close();
        return;
    }
    
    ofstream exportStream(GPIO_EXPORT_FILE);
    exportStream << m_pinID;
    exportStream.close();
}

Pin::Pin(unsigned pinID, Direction direction)
: Pin(pinID)
{
    setDirection(direction);
}

#pragma mark - Direction

#define DIRECTION_FILE "direction"
#define DIRECTION_IN_VALUE "in"
#define DIRECTION_OUT_VALUE "out"

Pin::Direction Pin::direction()
{
    return (readPinFile(DIRECTION_FILE).compare(DIRECTION_IN_VALUE) == 0) ? DirectionIn : DirectionOut;
}

void Pin::setDirection(Direction direction)
{
    writePinFile(DIRECTION_FILE, (direction == DirectionIn) ? DIRECTION_IN_VALUE : DIRECTION_OUT_VALUE);
}

#pragma mark - Value

#define VALUE_FILE "value"
#define VALUE_HIGH_VALUE "1"
#define VALUE_LOW_VALUE "0"

Pin::Value Pin::value()
{
    return (readPinFile(VALUE_FILE).compare(VALUE_HIGH_VALUE) == 0) ? ValueHigh : ValueLow;
}

void Pin::setValue(Value value)
{
    writePinFile(VALUE_FILE, (value == ValueHigh) ? VALUE_HIGH_VALUE : VALUE_LOW_VALUE);
}

#pragma mark - Utility

string Pin::readPinFile(string filename)
{
    ifstream in(m_pinDir + filename);
    if (!in.is_open())
        return nullptr;
    
    string value;
    getline(in, value);
    in.close();
    return value;
}

void Pin::writePinFile(string filename, string value)
{
    ofstream out(m_pinDir + filename);
    if (!out.is_open())
        return;
    
    out << value;
    out.close();
}
