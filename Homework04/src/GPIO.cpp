#include "GPIO.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace ECE;

string GPIO::readPinFile(string filename)
{
    string file = m_pinDir + filename;
    int fd = open(file.c_str(), O_RDONLY);
    if (fd < 0)
    {
        perror(file.c_str());
        return "";
    }

    static unsigned const MaxBufferLength = 10;
    char buffer[MaxBufferLength];
    read(fd, buffer, MaxBufferLength);
    close(fd);

    for (unsigned idx = 0; idx < MaxBufferLength; ++idx)
        if (isspace(buffer[idx]))
        {
            buffer[idx] = '\0';
            break;
        }

    return string(buffer);
}

void GPIO::writePinFile(string filename, string value)
{
    string file = m_pinDir + filename;
    int fd = open(file.c_str(), O_WRONLY);
    if (fd < 0)
    {
        perror(file.c_str());
        return;
    }

    write(fd, value.c_str(), value.length());
    close(fd);
}
