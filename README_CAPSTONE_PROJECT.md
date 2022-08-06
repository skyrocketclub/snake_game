## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## Extension of the Snake Game (Expected Behaviour)
  
  1. The main extension of the game is the adding of the Highscore feature
  2. The program automatically creates a text file (highscore.txt) at the beginning of the program if one does not already exist and it saves the value of 0 in the file.
  3. Upon playing the game, the current Highscore is being displayed so that it motivates the player to score up to that highscore
  4. When the snake dies, the upper window either shows "Game Over" or "New High Score" depending on if the player beat the already existing highscore or not
  5. If there is a new hig score, the highscore.txt document is updated with the new value and upon playing the game the next time, the new Highscore is displayed.
  
  ## How submission satisfies the necessary rubric items
  
  The rubric points addressed and the criteria alongside where they are addressed in the code are shown below
  
  Rubric: Loops, Functions, I/O
  Criteria: The project demonstrates an understanding of C++ functions and control structures:
  Where in Code: game.h (lines 17, 31, 36, 37), game.cpp (lines 41 - 42, 75, 96 - 146) , renderer.h (line 14, 15, 16), renderer.cpp ( 41, 73 - 79, 88 - 96)
  
  Criteria: The project reads data from a file and process the data, or the program writes data to a file.
  Where in Code:  game.cpp (Lines 4, 97 - 111, 117 - 130, 143 - 146)
  
  Rubric: Object Oriented Programming
  Criteria: The project uses Object Oriented Programming techniques.
  Criteria: Classes use appropriate access specifiers for class members.
  Where in Code: game.h (lines 96 - 136), renderer.cpp (lines 94 - 96)
  

  