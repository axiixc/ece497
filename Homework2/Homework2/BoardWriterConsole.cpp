//
//  BoardWriterConsole.cpp
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "BoardWriterConsole.h"

#include "ConsoleSupport.h"

BoardWriterConsole::BoardWriterConsole()
: BoardWriter()
{
    ConsoleSupport::sharedConsole().setNeedsConsoleSession();
}

void BoardWriterConsole::updateDisplay()
{
    WINDOW* window = ConsoleSupport::sharedConsole().window();
    
    wclear(window);
    for (int yIdx = 0; yIdx < m_data.size(); ++yIdx)
    {
        std::vector<BoardPositionState> row = m_data[yIdx];
        for (int xIdx = 0; xIdx < row.size(); ++xIdx)
        {
            wmove(window, xIdx, yIdx * 2);
            wattr_set(window, m_cursorPosition.isPoint(xIdx, yIdx) ? WA_REVERSE : WA_NORMAL, 0, NULL);
            wprintw(window, (row[xIdx] == BoardPositionStateHigh) ? "#" : ".");
        }
    }
}
