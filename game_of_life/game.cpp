#include "game.h"

#include <iostream>

// sanity intialize members
Game::Game() :
    m_board1(nullptr),
    m_board2(nullptr),
    m_useBoard1(true),
    m_sizeX(0),
    m_sizeY(0){
}

Game::~Game(){
    // make sure clean shutdown
    Shutdown();
}

bool
Game::Init(uint32_t x, uint32_t y){
    m_sizeX = x;
    m_sizeY = y;

    m_board1 = std::make_unique<Board>();
    m_board2 = std::make_unique<Board>();

    // if boards don't init, shut it down
    if(!m_board1 || !m_board2 || !m_board1->Init(x,y) || !m_board2->Init(x,y)){
        Shutdown();
        return false;
    }

    return true;
}

void
Game::Shutdown(){
    if(m_board1){
        m_board1->Shutdown();
        m_board1 = nullptr;
    }
    if(m_board2){
        m_board2->Shutdown();
        m_board2 = nullptr;
    }
}

void
Game::LoopFor(uint64_t iterations){
    for( uint64_t i = 0; i < iterations; ++i){
        // debug print
        std::cout << "Processing iteration: "<< i + 1 << '\r';
        if(!Step()){
            std::cout << "No cells changed, ending early" << std::endl;
            return;
        }
    }
}

bool
Game::Step(void){
    bool changed = false;
    int32_t currXPos = 0;
    int32_t currYPos = 0;
    uint32_t alive = 0;

    // use accessor functions
    std::shared_ptr<Board> currentBoard = GetCurrentBoard();
    std::shared_ptr<Board> nextBoard = GetNextBoard();
    CopyBoard(currentBoard,nextBoard);

    for(uint32_t x = 0; x < m_sizeX; ++x){
        for(uint32_t y = 0; y < m_sizeY; ++y){
            // check grid around and get alive count
            // reset alive
            alive = 0;
            
            // debug print
            //std::cout << x << " " << y << std::endl;
            
            for(int xOffset = -1; xOffset < 2; ++xOffset){
                for(int yOffset = -1; yOffset < 2; ++yOffset){
                    // ignore own cell
                    if(!(xOffset == 0 && yOffset == 0)){
                        currXPos = x + xOffset;
                        currYPos = y + yOffset;

                        // only process if in bounds
                        if( currXPos >= 0 && currYPos >= 0 && currXPos < currentBoard->getXSize() && currYPos < currentBoard->getYSize()){
                            if(currentBoard->isAlive(currXPos,currYPos)){
                                alive++;
                            }
                        }

                        // check to see if need to switch state
                        if(currentBoard->isAlive(x,y)){
                            if(alive < 2 || alive > 3){
                                nextBoard->setCellStatus(x,y,false);
                                changed = true;
                            }
                        } else {
                            if(alive == 3){
                                nextBoard->setCellStatus(x,y,true);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
        if(!changed){
            return false;
        }
    }

    // done processing, swap boards
    SwapBoards();

    // debug print
    //Print();

    return true;
}

std::shared_ptr<Board>
Game::GetCurrentBoard(void){
    if(m_useBoard1){
        return m_board1;
    } else {
        return m_board2;
    }
}

std::shared_ptr<Board>
Game::GetNextBoard(void){
    if(m_useBoard1){
        return m_board2;
    } else {
        return m_board1;
    }
}

void
Game::SwapBoards(void){
    m_useBoard1 = !m_useBoard1;
}

void
Game::CopyBoard(std::shared_ptr<Board> src, std::shared_ptr<Board> dst){
    for(uint32_t x = 0; x < m_sizeX; ++x){
        for(uint32_t y = 0; y < m_sizeY; ++y){
            dst->setCellStatus(x,y,src->isAlive(x,y));
        }
    }
}

void
Game::SetCellStatus(uint32_t x, uint32_t y, bool alive){
    GetCurrentBoard()->setCellStatus(x,y,alive);
}

void
Game::Print(void){
    // print Live 1.06 header line
    std::cout << std::endl << "#Life 1.06" << std::endl;
    std::shared_ptr<Board> currentBoard = GetCurrentBoard();

    // run through the latest board and print out cordinates if alive
    // in Live 1.06 format
    for(int x = 0; x < currentBoard->getXSize(); ++x){
        for(int y = 0; y < currentBoard->getYSize(); ++y){
            if(currentBoard->isAlive(x,y)){
                std::cout << x << " " << y << std::endl;
            }
        }
    }
}