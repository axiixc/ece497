//
//  BoardWriterConsole.h
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef BoardWriterConsole_h
#define BoardWriterConsole_h

#include <iostream>
#include "BoardWriter.h"

class BoardWriterConsole : public BoardWriter {
public:
    BoardWriterConsole();
    
protected:
    virtual void updateDisplay();
};

#endif /* BoardWriterConsole_h */
