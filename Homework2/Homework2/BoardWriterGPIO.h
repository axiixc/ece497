//
//  BoardWriterGPIO.h
//  Homework2
//
//  Created by James Savage on 9/16/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef BoardWriterGPIO_h
#define BoardWriterGPIO_h

#include "BoardWriter.h"

class BoardWriterGPIO : public BoardWriter {
public:
    BoardWriterGPIO();
    
    void recievedMoveEvent(InputSource&, BoardDirection);
    
protected:
    virtual void updateDisplay();
    void clearAllLEDs();
    void turnOnLED(unsigned);
};

#endif /* BoardWriterGPIO_h */
