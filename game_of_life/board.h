#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdint.h>

class Board {
public:
    Board();                                // Contructor
    ~Board();                               // Destructor

    bool Init(uint32_t x, uint32_t y);      // initialize values
    void Shutdown(void);                    // shutdown and clean up

    uint32_t getXSize(void);
    uint32_t getYSize(void);

    bool isAlive(uint32_t x, uint32_t y);
    void setCellStatus(uint32_t x, uint32_t y, bool alive);

    void reset(void);

protected:
    uint64_t coordToArrayPos(uint32_t x, uint32_t y);

private:
    bool* m_board;
    uint32_t m_sizeX;
    uint32_t m_sizeY;
};

#endif
