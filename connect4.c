#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "gameplay.h"
#include "ai_player.h"
#include "output.h"

int main(int argc, char **argv)
{
	srand (time(NULL));
	board_type *board = createBoard(7,6);

	int input;
	while((winnerIs(board)==0) && validMovesLeft(board))
	{
		if(cp(board) == PLAYER_ONE)	
		{
			do
			{
				scanf("%d", &input);
				
				if(input < 0 || input > board->cols-1)
					printf("Provide a column number between 0 and %d\n", board->cols-1);
				else if(!validMove(board, input))
					printf("Column is full. Choose another one.\n");
				
			}while( input < 0 || input > board->cols-1 || !validMove(board, input) );
			
			makeMove(board,input);// Make it so!
		}
		else
			makeMove(board, getReasonedMove(board));// Make it so!

		toString(board);
	}
	return 0;
}