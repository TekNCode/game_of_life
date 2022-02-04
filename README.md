# game_of_life
## Game of Life, C++ Windows
### Steven Sandoval

### Code Explanation
Implimented requried features, but some quick ones for easy debugging.

#### Additional features:
- default board which sets up the board per instructions
- auto abort if board does not change.  if a board doesn't change in one iteration, it won't in the next iteration
- printing iterations so user is updated on status instead of waiting at blank screen for 50,000 iterations
- iterations and defaults are setup in Defines for easy change.

#### Code Decisions and Explanations
- Requirements broken down and created as modules so code is reusable.
- Worked on making make sure no overflows.  max value of 32 bit int * max value 32 bit int = max value of 64 bit.
- Could have used smaller variable types for this exact problem, but wouldn't be as moduler with the defines that could be changed.  e.g. current number of cells in 64,32 board is 2048 which could easily fit in a short, but if board size is increased by the provided defines, this could break and cause overflow.  Decided against memory optimization to allow easily change of defines without major code changes.
- decided on malloc and free of 2 game boards at initialization to speed up processing speed during iterations by just copying board values to another and then using a variable to toggle which is presented board.

### Requirements
- Impliment Conway's Game of Life
- 64-bit signed integer space.
- 64x32 grid
- Read state of simulation from std input
- run 50,000 iterations
- print result to standard output
  - Life 1.06 format
- Rules
  - "alive" cell becomes dead
    - less than 2 or more than 3 alive neighbors
  - "dead" cell becomes alive
    - *exactly* 3 alive neighbors
- Starting cells
```(0, 4)
(1, 3)
(1, 4)
(1, 5)
(3, 2)
(3, 3)
(3, 4)
(5, 0)
(5, 1)
(7, 0)
```

### Brainstorm/pre code notes
- main
  - handles input
  - initialize game class
- game class
  - creates board
  - destroys board
  - update x iterations ( separate step function )
  - pretty print ( Life 1.06 format?)
    - [Life 1.06 format](https://conwaylife.com/wiki/Life_1.06#:~:text=The%20Life%201.06%20file%20format,files%20are%20saved%20with%20a%20.&text=life%20file%20extension.)
- game board
  - stores game board
    - 2d array ( malloc? )
  - must store prev and current state
  - need to switch between boards ( pointers? )
