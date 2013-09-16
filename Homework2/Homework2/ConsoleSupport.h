//
//  ConsoleSupport.h
//  Homework1
//
//  Created by James Savage on 9/14/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#ifndef ConsoleSupport_h
#define ConsoleSupport_h

#include <curses.h>

class ConsoleSupport {
public:
    static ConsoleSupport& sharedConsole();
    
    void setNeedsConsoleSession();
    inline WINDOW* window() { return m_window; }
    
private:
    ConsoleSupport();
    
    WINDOW* m_window;
};

#endif /* ConsoleSupport_h */
