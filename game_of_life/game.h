#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"

#include <memory>

class Game {
public:
    Game();
    ~Game();

    bool Init(uint32_t x, uint32_t y);
    void Shutdown();

    void LoopFor(uint64_t iterations);
    bool Step(void);
    
    void SetCellStatus(uint32_t x, uint32_t y, bool alive);
    
    void Print(void);

protected:
    std::shared_ptr<Board> GetCurrentBoard(void);
    std::shared_ptr<Board> GetNextBoard(void);
    void SwapBoards(void);
    void CopyBoard(std::shared_ptr<Board> src, std::shared_ptr<Board> dst);

private:
    std::shared_ptr<Board> m_board1;
    std::shared_ptr<Board> m_board2;
    bool m_useBoard1;

    uint32_t m_sizeX;
    uint32_t m_sizeY;
};

#endif
