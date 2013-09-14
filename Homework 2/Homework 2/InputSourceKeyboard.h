//
//  InputSourceKeyboard.h
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef InputSourceKeyboard_h
#define InputSourceKeyboard_h

#include "InputSource.h"

class InputSourceKeyboard : public InputSource {
public:
    InputSourceKeyboard(InputSourceDelegate&);
    
    virtual void startRecievingInputEvents();
};

#endif /* InputSourceKeyboard_h */
