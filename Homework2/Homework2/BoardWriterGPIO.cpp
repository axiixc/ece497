//
//  BoardWriterGPIO.cpp
//  Homework2
//
//  Created by James Savage on 9/16/13.
//  Copyright (c) 2013 James Savage <me@axiixc.com>. All rights reserved.
//

#include "BoardWriterGPIO.h"

#include "gpio-utils.h"
#include "i2cbusses.h"
#include "i2c-dev.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

BoardWriterGPIO::BoardWriterGPIO()
: BoardWriter()
{
    char filename[200];
    m_i2cDevice = open_i2c_dev(lookup_i2c_bus("1"), filename, 200, 0);
    
    set_slave_addr(m_i2cDevice, parse_i2c_address("0x70"), 0);
    
    i2c_smbus_write_byte(m_i2cDevice, 0x21);
    i2c_smbus_write_byte(m_i2cDevice, 0x81);
    i2c_smbus_write_byte(m_i2cDevice, 0xe7);
}

void BoardWriterGPIO::clearAllLEDs()
{
}

void BoardWriterGPIO::updateDisplay()
{
    clearAllLEDs();
    
    static unsigned numberOfElements = 8;
    __u16 *board = (__u16*) calloc(numberOfElements, sizeof(__u16));
    
    for (int yIdx = 0; yIdx < m_data.size(); ++yIdx)
    {
        std::vector<BoardPositionState> row = m_data[yIdx];
        for (int xIdx = 0; xIdx < row.size(); ++xIdx)
        {
            if (row[xIdx] == BoardPositionStateHigh)
                board[xIdx] = board[xIdx] | (1 << yIdx);
            if (m_cursorPosition.isPoint(xIdx, yIdx))
                board[xIdx] = board[xIdx] | (1 << (yIdx + numberOfElements));
        }
    }
    
    i2c_smbus_write_i2c_block_data(m_i2cDevice, 0x00, 16, (__u8*) board);
    free(board);
}
