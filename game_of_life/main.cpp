#include <iostream>
#include <string>

#include "game.h"

// magic numbers bad!
#define DEFAULT_BOARD_SIZE_X 64
#define DEFAULT_BOARD_SIZE_Y 32
#define DEFAULT_ITERATIONS 50000

#define DEFAULT_BOARD_VALUE_COUNT 10
uint32_t defaultBoard[DEFAULT_BOARD_VALUE_COUNT][2] = {
{0,4},
{1,3},
{1,4},
{1,5},
{3,2},
{3,3},
{3,4},
{5,0},
{5,1},
{7,0}
};

int main(int argc, char** argv)
{
    // declare initial variables
    std::string response;
    std::string::size_type stringSize;
    std::unique_ptr<Game> game = std::make_unique<Game>();

    // setup game board
    if(!game->Init(DEFAULT_BOARD_SIZE_X,DEFAULT_BOARD_SIZE_Y)){
        std::cout << "Error, unable to initalize game. Exiting." << std::endl;
        game->Shutdown();
        return -1;
    }

    // print banner and instructions
    std::cout << "Game of Life" << std::endl;
    std::cout << "Steven Sandoval" << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "'d' to load default game" << std::endl;
    std::cout << "'i' to input cells manually" << std::endl;
  
    // get reponse
    std::cin >> response;
    std::cout << std::endl;

    // if 'd' load default game ( quickest for testing )
    if( response.compare("d") == 0 ){
        for(int i = 0; i < DEFAULT_BOARD_VALUE_COUNT; ++i){
            game->setCellStatus(defaultBoard[i][0],defaultBoard[i][1],true);
        }
    } else {    // if 'i' or any other value is used, assume not default and get board info
        // else variables
        int32_t numInputCells = 0;
        std::string delim = ",";
        std::string xCordString;
        std::string yCordString;

        // string sanitize
        response.clear();

        // get number of cells
        std::cout << "Enter the number of input cell(s): ";
        std::cin >> response;

        // todo: sanity check input
        numInputCells = std::stoi(response, &stringSize);
        
        for(int i = 0; i < numInputCells; ++i ){
            // string sanitize
            response.clear();

            std::cout << "Enter alive cell " << i+1 << " cordinate with syntax x,y:";
            std::cin >> response;

            // todo: santiy check input
            size_t delimPos = response.find(delim);
            xCordString = response.substr(0,delimPos);
            yCordString = response.substr(delimPos+1);

            // todo: sanity check
            int32_t xPos = std::stoi(xCordString, &stringSize);
            int32_t yPos = std::stoi(yCordString, &stringSize);

            // todo: call game class
            game->setCellStatus(xPos,yPos,true);
        }

    }
    
    std::cout << "Game setup completed.  Start game (Y/n)";
    std::cin >> response;

    // most common condition is Y
    if((response.compare("Y") == 0) || (response.compare("y") == 0)) {
        
        // run iterations
        game->LoopFor(DEFAULT_ITERATIONS);

        // print result
        game->print();
    }

    // cleanup time
    std::cout << "Exiting.";
    game->Shutdown();

    return 0;
}