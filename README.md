Connect4 is a two-player connection game in which the players take turns dropping their tokens from the top into a seven-column, six-row grid. The tokens fall straight down, occupying the next available space within the column. The object of the game is to connect four of one's own tokens next to each other vertically, horizontally, or diagonally before your opponent.

In order to play the game compile it and run it by typing:

	$ make
	$ ./connect4

and then follow the on-screen instructions.

The testing framework automatically compiles with the root Makefile. If you want to compile it separatelly then type:

	$ cd testing/
	$ make

It can be ran by typing:

	$ cd testing/
	$ ./test-all
