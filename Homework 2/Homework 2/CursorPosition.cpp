//
//  CursorPosition.cpp
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "CursorPosition.h"

CursorPosition::CursorPosition()
{
}

CursorPosition::CursorPosition(int x, int y)
: tuple(x, y)
{
}

CursorPosition& CursorPosition::move(BoardDirection direction)
{
    switch (direction)
    {
        case BoardDirectionNorth: return *new CursorPosition(x() - 1, y());
        case BoardDirectionEast:  return *new CursorPosition(x(), y() + 1);
        case BoardDirectionSouth: return *new CursorPosition(x() + 1, y());
        case BoardDirectionWest:  return *new CursorPosition(x(), y() - 1);
    }
}