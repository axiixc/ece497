#include "Pin.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static const string GPIODirectory = "/sys/class/gpio/gpio";
static const string GPIOExportFile = "/sys/class/gpio/export";

using namespace ECE;

Pin::Pin(unsigned pinID)
: m_pinID(pinID)
{
    m_pinDir = GPIODirectory + std::to_string(pinID) + "/";

    int fd = open(GPIOExportFile.c_str(), O_WRONLY);
    if (fd < 0)
    {
        perror(GPIOExportFile.c_str());
        return;
    }

    string value = std::to_string(pinID);
    write(fd, std::to_string(pinID).c_str(), value.length());
    close(fd);
}

Pin::Pin(unsigned pinID, Direction direction)
: Pin(pinID)
{
    setDirection(direction);
}

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

#define VALUE_FILE "value"
#define VALUE_HIGH_VALUE "1"
#define VALUE_LOW_VALUE "0"

Pin::Value Pin::value()
{
    string pinValue = readPinFile(VALUE_FILE);
    return (pinValue.compare(VALUE_HIGH_VALUE) == 0) ? ValueHigh : ValueLow;
}

void Pin::setValue(Value value)
{
    writePinFile(VALUE_FILE, (value == ValueHigh) ? VALUE_HIGH_VALUE : VALUE_LOW_VALUE);
}
