//
//  InputSourceGPIO.cpp
//  Homework 2
//
//  Created by James Savage on 9/15/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "InputSourceGPIO.h"

#include <assert.h>
#include <csignal>
#include <fcntl.h>
#include <iostream>
#include "gpio-utils.h"
#include <string.h>
#include <unistd.h>

// TODO: Arrange these later
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

static unsigned const GPIOPinNorth = 30;
static unsigned const GPIOPinEast = 31;
static unsigned const GPIOPinSouth = 48;
static unsigned const GPIOPinWest = 3;

static unsigned GPIOPins[] = { GPIOPinNorth, GPIOPinEast, GPIOPinSouth, GPIOPinWest };

static inline BoardDirection translatePinToDirection(unsigned pin)
{
    switch (pin)
    {
        case GPIOPinNorth: return BoardDirectionNorth;
        case GPIOPinEast: return BoardDirectionEast;
        case GPIOPinSouth: return BoardDirectionSouth;
        case GPIOPinWest: return BoardDirectionWest;
        default: return BoardDirectionInvalid;
    }
}

bool processingEvents = false;

InputSourceGPIO::InputSourceGPIO(InputSourceDelegate& delegate)
: InputSource(delegate)
, m_pinDescriptors(0)
{
}

void handleSignal(int signal)
{
    processingEvents = false;
}

void InputSourceGPIO::startRecievingInputEvents()
{
    performPollSetup();
    turnRunLoop();
}

void InputSourceGPIO::turnRunLoop()
{
    while (processingEvents)
        performPoll();
    performPollTeardown();
    exit(0);
}

void InputSourceGPIO::performPollSetup()
{
    processingEvents = true;
    
    std::signal(SIGINT, &handleSignal);
    
    m_pinDescriptors = (struct pollfd *) malloc(sizeof(struct pollfd) * 5);
    m_pinDescriptors[0] = { .fd = STDIN_FILENO, .events = POLLIN };
    
    for (unsigned idx = 0; idx < 4; ++idx)
    {
        unsigned port = GPIOPins[idx];
        gpio_export(port);
        gpio_set_dir(port, "in");
        gpio_set_edge(port, "both");
        m_pinDescriptors[idx + 1] = {
            .fd = gpio_fd_open(port, O_RDONLY),
            .events = POLLPRI
        };
    }
}

void InputSourceGPIO::performPoll()
{
    static int const PollTimeout = 3000; // 3 seconds
    int numberOfEvents = poll(m_pinDescriptors, 5, PollTimeout);
    
    if (numberOfEvents < 0)
    {
        fprintf(stderr, "poll() failed with error %d\n", errno);
        exit(errno);
    }
    
    if (numberOfEvents == 0)
        return;
    
    for (unsigned idx = 1; idx < 5; ++idx)
    {
        fprintf(stderr, "check pin %u \n", idx);
        struct pollfd gpio = m_pinDescriptors[idx];
        if (!(gpio.revents & POLLPRI))
            continue;
        
        lseek(gpio.fd, 0, SEEK_SET);
        char buffer[MAX_BUF];
        read(gpio.fd, buffer, sizeof(buffer));
        
        fprintf(stderr, "Read %s", buffer);
        
        if ('0' != buffer[0])
            continue;
        
        // NOTE: Off-by-one between fdarray and GPIOPins, swap stdin to pos 4 to fix
        fprintf(stderr, "Pushed pin %u\n", GPIOPins[idx-1]);
        m_delegate.recievedMoveEvent(*this, translatePinToDirection(GPIOPins[idx-1]), BoardPositionStateHigh);
    }
}

void InputSourceGPIO::performPollTeardown()
{
    for (unsigned idx = 1; idx < 5; ++idx)
        gpio_fd_close(m_pinDescriptors[idx].fd);
}
