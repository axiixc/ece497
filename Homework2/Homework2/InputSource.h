//
//  InputSource.h
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef InputSource_h
#define InputSource_h

#include <vector>

#include "BoardTypes.h"

class InputSource;

class InputSourceDelegate {
public:
    virtual void recievedMoveEvent(InputSource&, BoardDirection, BoardPositionState) = 0;
    virtual void receivedClearEvent(InputSource&) = 0;
};

class InputSourceDelegateDuplexer : public InputSourceDelegate {
public:
    InputSourceDelegateDuplexer();
    inline InputSourceDelegate& operator<<(InputSourceDelegate& listener) { m_listeners.push_back(&listener); return listener; };
    
    virtual void recievedMoveEvent(InputSource&, BoardDirection, BoardPositionState);
    virtual void receivedClearEvent(InputSource&);
    
    std::vector<InputSourceDelegate*> m_listeners;
};

class InputSource {
public:
    template <class T> static InputSource& create(InputSourceDelegate& delegate)
    {
        return static_cast<T&>(*new T(delegate));
    };
    
    virtual void startRecievingInputEvents() = 0;
    
protected:
    InputSource(InputSourceDelegate&);
    
    InputSourceDelegate& m_delegate;
    BoardPositionState m_writeState;
};

#endif /* InputSource_h */
