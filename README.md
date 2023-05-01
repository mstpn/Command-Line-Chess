# Command Line Chess
A chess application with a multithreaded alpha-beta search chess AI that runs in the command line. 

## Build
`cd` into the `Command-Line-Chess` folder  
run `make`   
play game with `./game`

## Gameplay
### Multithreading
Your CPU will be analyzed and the number of threads for the game will be set to 2x core count. You can choose to accept this, or manually select the number of threads to use for calculation.

### Colour
You can choose to play as white, black, a random colour, or watch an AI match.

### Difficulty
There are three difficulty settings:
- Easy moves are instantaneous
- Normal moves take a few seconds
- Hard moves may take 30-60s+ in some positions.  

The difficulty is based off of the depth level for the search (deeper == harder).

### Moves
Moves are made using [Algebraic Notation](https://en.wikipedia.org/wiki/Algebraic_notation_(chess)). Enter the coordinates of the piece you wish to move (upper or lower case), then enter the coordinates of the square you wish to move it to.  

For example, to move the white pawn at e2 to e4:
- e2 -> ENTER
- e4 -> ENTER  

Enter -1 to exit the program.

## Developing
Place your files in the `clcp` folder  
Modify the makefile INSIDE the `clcp` folder to build your code  
Make sure to add your files to the bottom of the makefile, then append the name of your `*.o` module to the `MODULES` variable at the top  

## GoogleTest
If you have GoogleTest set up on your system, you can run make all to run the gcov and gtest suites. Note that you must uncomment the GTFLAGS line (8) in the makefile first, as it has been disabled to allow make to build properly on systems without gtest.