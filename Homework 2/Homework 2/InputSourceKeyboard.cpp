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
            case 'w': m_delegate.recievedMoveEvent(*this, BoardDirectionNorth); break;
            case 's': m_delegate.recievedMoveEvent(*this, BoardDirectionSouth); break;
            case 'a': m_delegate.recievedMoveEvent(*this, BoardDirectionWest); break;
            case 'd': m_delegate.recievedMoveEvent(*this, BoardDirectionEast); break;
            case 'q':
            case 'e': m_delegate.receivedClearEvent(*this); break;
            default: break;
        }
    }
}
