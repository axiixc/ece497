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
#include <string>

static std::string const IOSourceKeyboard = "keyboard";

int main(int argc, const char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage %s <input = keyboard|gpio> <output = keyboard|gpio>\n", argv[0]);
        return -1;
    }
    
    std::string boardWriterType(argv[1]);
    BoardWriter& boardWriter = (boardWriterType.compare(IOSourceKeyboard) == 0) ?
        BoardWriter::create<BoardWriterConsole>() :
        BoardWriter::create<BoardWriterGPIO>();
    
    std::string inputSourceType(argv[2]);
    InputSource& inputSource = (inputSourceType.compare(IOSourceKeyboard) == 0) ?
        InputSource::create<InputSourceKeyboard>(boardWriter) :
        InputSource::create<InputSourceGPIO>(boardWriter);
    
    inputSource.startRecievingInputEvents();
    return 0;
}

