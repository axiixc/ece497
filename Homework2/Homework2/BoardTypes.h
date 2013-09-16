//
//  BoardTypes.h
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef BoardTypes_h
#define BoardTypes_h

typedef enum {
    BoardDirectionInvalid = -1,
    BoardDirectionNorth,
    BoardDirectionEast,
    BoardDirectionSouth,
    BoardDirectionWest,
} BoardDirection;

typedef enum {
    BoardPositionStateLow = 0,
    BoardPositionStateHigh = 1,
} BoardPositionState;

#endif /* BoardTypes_h */