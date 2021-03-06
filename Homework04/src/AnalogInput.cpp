#include "AnalogInput.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static const string AINDirectory = "/sys/devices/ocp.2/helper.14/AIN";

using namespace ECE;

AnalogInput::AnalogInput(unsigned AnalogInputID)
: m_analogInputID(AnalogInputID)
{
    m_pinDir = AINDirectory + std::to_string(AnalogInputID);
}

int AnalogInput::value()
{
    return atoi(readPinFile("").c_str());
}

static const string slots = "/sys/devices/bone_capemgr.8/slots";
static const string analogEnable = "cape-bone-iio";

void AnalogInput::initialize()
{
    int fd = open(slots.c_str(), O_WRONLY);
    if (fd < 0)
    {
        perror(slots.c_str());
        return;
    }
    
    write(fd, analogEnable.c_str(), analogEnable.length());
    close(fd);
}
