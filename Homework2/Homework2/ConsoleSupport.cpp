//
//  ConsoleSupport.cpp
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "ConsoleSupport.h"

ConsoleSupport& ConsoleSupport::sharedConsole()
{
    static ConsoleSupport& sharedConsole = *new ConsoleSupport();
    return sharedConsole;
}

ConsoleSupport::ConsoleSupport()
: m_window(NULL)
{
}

void ConsoleSupport::setNeedsConsoleSession()
{
    if (m_window) return;
    
    m_window = initscr();
    cbreak();
    noecho();
}