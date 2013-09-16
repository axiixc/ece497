//
//  main.cpp
//  Homework1
//
//  Created by James Savage on 9/13/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "BoardWriterConsole.h"
#include "BoardWriterGPIO.h"
#include "InputSourceGPIO.h"
#include "InputSourceKeyboard.h"

#include <stdio.h>
#include <string.h>

int main(int argc, const char **argv)
{
    if (argc == 2 && strncmp("--keyboard", argv[1], strlen("--keyboard")) == 0)
        InputSource::create<InputSourceKeyboard>(BoardWriter::create<BoardWriterConsole>()).startRecievingInputEvents();
    else
        InputSource::create<InputSourceGPIO>(BoardWriter::create<BoardWriterGPIO>()).startRecievingInputEvents();
    
    return 0;
}

