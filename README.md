# game_of_life
## Game of Life, C++ Windows

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
(7, 0)```

### Implimentation
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