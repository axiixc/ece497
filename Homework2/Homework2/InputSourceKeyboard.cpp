//
//  InputSourceKeyboard.cpp
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "InputSourceKeyboard.h"

#include "ConsoleSupport.h"

InputSourceKeyboard::InputSourceKeyboard(InputSourceDelegate& delegate)
: InputSource(delegate)
{
    ConsoleSupport::sharedConsole().setNeedsConsoleSession();
}

void InputSourceKeyboard::startRecievingInputEvents()
{
    int key;
    while ((key = getch()))
    {
        switch (key)
        {
            case 'w': m_delegate.recievedMoveEvent(*this, BoardDirectionNorth, m_writeState); break;
            case 's': m_delegate.recievedMoveEvent(*this, BoardDirectionSouth, m_writeState); break;
            case 'a': m_delegate.recievedMoveEvent(*this, BoardDirectionWest, m_writeState); break;
            case 'd': m_delegate.recievedMoveEvent(*this, BoardDirectionEast, m_writeState); break;
            case 'q': m_delegate.receivedClearEvent(*this); break;
            case 'e': m_writeState = !m_writeState;
            default: break;
        }
    }
}
