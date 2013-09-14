//
//  BoardWriter.cpp
//  Homework1
//
//  Created by James Savage on 9/13/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "BoardWriter.h"

#include <assert.h>
#include "BoardWriterConsole.h"

const size_t BoardSize = 8;

BoardWriter::BoardWriter()
: m_data(BoardSize)
, m_cursorPosition(0, 0)
{
    for (auto i = 0; i < BoardSize; ++i)
        m_data[i] = *new std::vector<BoardPositionState>(BoardSize);
}

void BoardWriter::resetBoard()
{
    for (auto i = 0; i < m_data.size(); ++i)
        for (auto j = 0; j < m_data[i].size(); ++j)
            m_data[i][j] = m_cursorPosition.isPoint(j, i) ? BoardPositionStateHigh : BoardPositionStateLow;
    
    updateDisplay();
}

void BoardWriter::resetCursor()
{
    m_cursorPosition = *new CursorPosition();
    updateDisplay();
}

void BoardWriter::recievedMoveEvent(InputSource& inputSource, BoardDirection direction)
{
    CursorPosition newPosition = m_cursorPosition.move(direction);
    if (!newPosition.isInsideBounds(m_data.size()))
        return;
    
    m_cursorPosition = newPosition;
    m_data[m_cursorPosition.y()][m_cursorPosition.x()] = BoardPositionStateHigh;
    
    updateDisplay();
}
