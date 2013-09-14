//
//  BoardWriter.h
//  Homework1
//
//  Created by James Savage on 9/13/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef BoardWriter_h
#define BoardWriter_h

#include <vector>

#include "BoardTypes.h"
#include "CursorPosition.h"
#include "InputSource.h"

class BoardWriter : public InputSourceDelegate {
public:
    template <class T> static T& create()
    {
        BoardWriter& writer = *new T();
        writer.resetBoard();
        
        return static_cast<T&>(writer);
    };
    
    void resetBoard();
    void resetCursor();
    
    void recievedMoveEvent(InputSource&, BoardDirection);
    inline virtual void receivedClearEvent(InputSource&) { resetBoard(); };
    
protected:
    BoardWriter();
    
    virtual void updateDisplay() = 0;
    
    std::vector<std::vector<BoardPositionState>> m_data;
    CursorPosition m_cursorPosition;
};

#endif /* BoardWriter_h */
