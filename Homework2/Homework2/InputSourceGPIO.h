//
//  InputSourceGPIO.h
//  Homework 2
//
//  Created by James Savage on 9/15/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef InputSourceGPIO_h
#define InputSourceGPIO_h

#include "InputSource.h"

#include <poll.h>
#include <vector>

class InputSourceGPIO : public InputSource {
public:
    InputSourceGPIO(InputSourceDelegate&);
    
    virtual void startRecievingInputEvents();
    
private:
    std::vector<struct pollfd> m_pinDescriptors;
    
    void turnRunLoop();
    
    void performPollSetup();
    void performPoll();
    void performPollTeardown();
};

#endif /* InputSourceGPIO_h */
