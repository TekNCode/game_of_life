#include "board.h"

#include <stdlib.h>
#include <string.h>  // for malloc

// sanity intialize members
Board::Board() :
    m_board(nullptr),
    m_sizeX(0),
    m_sizeY(0){
}


Board::~Board(){
    // make sure clean shutdown
    Shutdown();
}

bool
Board::Init(uint32_t x, uint32_t y){
    m_sizeX = x;
    m_sizeY = y;

    //todo: sanity check for overflow
    uint64_t size = x * y;

    if( size <= 0 ){
        return false;
    }

    //size of bool used for sanity.  could be left out
    m_board = reinterpret_cast<bool*>(malloc(size*sizeof(bool)));

    if(!m_board){
        return false;
    }

    reset();

    return true;
}

void
Board::Shutdown(void){
    if(m_board){
        free(m_board);
        m_board = nullptr;
    }
}

uint32_t
Board::getXSize(void){
    return m_sizeX;
}

uint32_t
Board::getYSize(void){
    return m_sizeY;
}

bool
Board::isAlive(uint32_t x, uint32_t y){
    if(!m_board || x < 0 || y < 0 || x >= m_sizeX || y >= m_sizeY){
        return false;
    }

    // pointer math to access malloc'd mem
    return m_board[coordToArrayPos(x,y)];
}

void
Board::setCellStatus(uint32_t x, uint32_t y, bool alive){
    //todo: move sanity check to function, used more than once
    if(!m_board || x < 0 || y < 0 || x >= m_sizeX || y >= m_sizeY){
        return;
    }

    uint64_t coord = coordToArrayPos(x,y);
    m_board[coord] = alive;
}

uint64_t
Board::coordToArrayPos(uint32_t x, uint32_t y){
    if(!m_board || x < 0 || y < 0 || x >= m_sizeX || y >= m_sizeY){
        return 0;
    }

    uint64_t coord = (y*m_sizeX) + x;
    return coord;
}

void
Board::reset(void){
    if(!m_board){
        return;
    }
    //todo: sanity check for overflow
    uint64_t size = m_sizeX * m_sizeY;
    memset(m_board, NULL, size*sizeof(bool));
}
