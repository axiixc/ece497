//
//  InputSource.cpp
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "InputSource.h"

InputSourceDelegateDuplexer::InputSourceDelegateDuplexer()
: m_listeners(0)
{
}

void InputSourceDelegateDuplexer::receivedClearEvent(InputSource& inputSource)
{
    for (std::vector<InputSourceDelegate*>::iterator listener = m_listeners.begin(); listener != m_listeners.end(); ++listener)
        if (*listener) (*listener)->receivedClearEvent(inputSource);
}

void InputSourceDelegateDuplexer::recievedMoveEvent(InputSource& inputSource, BoardDirection direction, BoardPositionState writeState)
{
    for (std::vector<InputSourceDelegate*>::iterator listener = m_listeners.begin(); listener != m_listeners.end(); ++listener)
        if (*listener) (*listener)->recievedMoveEvent(inputSource, direction, writeState);
}

InputSource::InputSource(InputSourceDelegate& delegate)
: m_delegate(delegate)
, m_writeState(BoardPositionStateHigh)
{
}
