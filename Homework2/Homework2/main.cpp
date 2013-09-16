//
//  main.cpp
//  Homework1
//
//  Created by James Savage on 9/13/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "BoardWriterConsole.h"
#include "InputSourceKeyboard.h"

int main(int argc, const char * argv[])
{
    BoardWriter& writer = BoardWriter::create<BoardWriterConsole>();
    InputSource& inputSource = InputSource::create<InputSourceKeyboard>(writer);
    inputSource.startRecievingInputEvents();
    
    return 0;
}

