//
//  BoardWriterGPIO.cpp
//  Homework2
//
//  Created by James Savage on 9/16/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "BoardWriterGPIO.h"

#include "gpio-utils.h"
#include "stdio.h"

static unsigned const GPIOPinInvalid = 0;
static unsigned const GPIOPinNorth = 60;
static unsigned const GPIOPinEast = 50;
static unsigned const GPIOPinSouth = 51;
static unsigned const GPIOPinWest = 2;

static unsigned GPIOPins[] = { GPIOPinNorth, GPIOPinEast, GPIOPinSouth, GPIOPinWest };

static inline unsigned translateDirectionToPin(BoardDirection direction)
{
    switch (direction)
    {
        case BoardDirectionNorth: return GPIOPinNorth;
        case BoardDirectionEast: return GPIOPinEast;
        case BoardDirectionSouth: return GPIOPinSouth;
        case BoardDirectionWest: return GPIOPinWest;
        default: return GPIOPinInvalid;
    }
}

BoardWriterGPIO::BoardWriterGPIO()
: BoardWriter()
{
    for (unsigned idx = 0; idx < 4; ++idx)
    {
        gpio_export(GPIOPins[idx]);
        gpio_set_dir(GPIOPins[idx], "out");
    }
    
    clearAllLEDs();
}

void BoardWriterGPIO::recievedMoveEvent(InputSource& inputSource, BoardDirection direction)
{
    clearAllLEDs();
    
    unsigned pin = translateDirectionToPin(direction);
    if (pin != GPIOPinInvalid)
        turnOnLED(pin);
    else
        fprintf(stderr, "Invalid board direction, something is wrong?!\n");
}

void BoardWriterGPIO::clearAllLEDs()
{
    for (unsigned idx = 0; idx < 4; ++idx)
        gpio_set_value(GPIOPins[idx], false);
}

void BoardWriterGPIO::turnOnLED(unsigned pin)
{
    gpio_set_value(pin, true);
    fprintf(stderr, "Turn on LED: %u", pin);
}

void BoardWriterGPIO::updateDisplay()
{
}
