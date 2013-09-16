//
//  CursorPosition.h
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef CursorPosition_h
#define CursorPosition_h

#include <tuple>

#include "BoardTypes.h"

struct CursorPosition : private std::tuple<int,int> {
public:
    CursorPosition();
    CursorPosition(int, int);
    
    inline int x() { return std::get<0>(*this); };
    inline int y() { return std::get<1>(*this); };
    
    CursorPosition& move(BoardDirection direction);
    inline bool isInsideBounds(int bounds) { return x() >= 0 && y() >= 0 && x() < bounds && y() < bounds; };
    inline bool isPoint(int _x, int _y) { return x() == _x && y() == _y; };
};

#endif /* CursorPosition_h */
