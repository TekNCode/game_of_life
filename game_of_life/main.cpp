#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    // declare initial variables
    std::string response;
    std::string::size_type stringSize;

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
        bool done = false;
        while(!done){
            
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
            int32_t delimPos = response.find(delim);
            xCordString = response.substr(0,delimPos);
            yCordString = response.substr(delimPos+1);

            // todo: call game class
            // setCellAlive(x,y)
        }

    }
    
    std::cout << "Game setup completed.  Start game (Y/n)";
    std::cin >> response;

    // most common condition is Y
    if((response.compare("Y") == 0) || (response.compare("y") == 0)) {
        //todo: game loop
        //runFor(50000);

        //todo: print result
        //print();
    }

    std::cout << "Exiting.";
    return 0;
}