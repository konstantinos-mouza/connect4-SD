#include <stdio.h>
#include <stdlib.h>

#include "gameplay.h"


point_type * newPoint(int a, int b)
{
	point_type *point = (point_type*)malloc(sizeof(point_type));
	point->x = a;
	point->y = b;
	point->state = EMPTY;
	return point;
}


void deletepoint(point_type *point)
{
	free(point);
}


int equalsPosition(point_type * a, point_type* b)
{
	return (a->x == b->x) && (a->y == b->y); //added parenthesis for readability
}


void setState(point_type *point, int player)
{
	point->state = player;
}


int getState(point_type *point)
{
	return point->state;
}


point_type*** generateCL(point_type ***grid)
{
	int i, y, x, t;
	int count = 0;
	
	point_type ***lines = (point_type ***)malloc(QUARTETS * sizeof(point_type **));
	if(!lines)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}
	for(i=0; i<QUARTETS; i++)
	{
		lines[i] = (point_type **)malloc(4 * sizeof(point_type *));
		if(!lines[i])
		{
			printf("Not enough memory. Exiting...\n");
			exit(-1);
		}
	}

	for(y=0; y<6; y++)
	{
		for(x=0; x<4; x++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(i=x; i<x+4; i++)
			{
				temp[i-x] = grid[i][y];
			}
			lines[count] = temp;
			count++;
		}
	}

	for(x=0; x<7; x++)
	{
		for(y=0; y<3; y++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(i=y; i<y+4; i++)
			{
				temp[i-y] = grid[x][i];
			}
			lines[count] = temp;
			count++;
		}
	}

	for(x=0; x<4; x++)
	{
		for(y=0; y<3; y++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(t=x,i=y; t<x+4 && i<y+4; t++,i++)
			{
				temp[i-y] = grid[t][i];
			}
			lines[count] = temp;
			count++;
		}
	}
	
	for(x=0; x<4; x++)
	{
		for(y=5; y>2; y--)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(t=x,i=y; t<x+4 && i>-1; t++,i--)
			{
				temp[t-x] = grid[t][i];
			}
			lines[count] = temp;
			count++;
		}
	}
	
	return lines;
}


board_type * createBoard(int a, int b)
{
	board_type *board = (board_type*)malloc(sizeof(board_type));
	board->cols=a;
	board->rows=b;
	board->lm=-1;
	board->cp=PLAYER_ONE;
	board->heights = (int *)malloc(board->cols * sizeof(int));
	board->grid = (point_type ***)malloc(board->cols * sizeof(point_type **));
	int x;
	int y;
	for(x = 0; x < board->cols; x++)
	{
		board->grid[x] =(point_type **)malloc(board->rows * sizeof(point_type *));
		board->heights[x] = 0;
		for(y = 0; y< board->rows; y++)
		{
			board->grid[x][y] = newPoint(x,y);
		}
	}
	board->moves = (int *)malloc(board->cols * board->rows * sizeof(int));

	board->cl = generateCL(board->grid);
	return board;
}


void deleteboard(board_type* board)
{
	free(board->cl);
	free(board->grid);
	free(board->heights);
	free(board->moves);
	free(board);
}


int validMove(board_type *board, int column)
{
	return (board->heights[column] < board->rows);
}


void makeMove(board_type *board, int column)
{
	int row = board->heights[column];
	
	setState(board->grid[column][row], board->cp);

	board->heights[column]++;
	board->lm++;
	board->moves[board->lm] = column;
	board->cp = -board->cp;
}


void undoMove(board_type *board)
{
	int column = board->moves[board->lm];
	int row = board->heights[board->moves[board->lm]]-1;
	
	setState(board->grid[column][row], EMPTY);
	
	board->heights[column]--;
	board->lm--;
	board->cp = -board->cp;
}


int validMovesLeft(board_type *board)
{
	return board->lm < ((board->cols * board->rows)-1);
}


int getScore(point_type **points)
{
	int playerone=0;
	int playertwo=0;
	int i;
	
	for(i=0; i<4; i++)
	{
		if(getState(points[i]) == PLAYER_ONE)
			playerone++;
		else if(getState(points[i]) == PLAYER_TWO)
			playertwo++;
	}
	
	if( (playerone+playertwo>0) && (!(playerone>0 && playertwo>0)) )
		return (playerone != 0) ? playerone : playertwo;
	else
		return 0;
}


int winnerIs(board_type *board)
{
	int i;
	
	for(i=0; i<QUARTETS; i++)
	{
		if(getScore(board->cl[i]) == 4)
			return PLAYER_ONE;
		else if(getScore(board->cl[i]) == -4)
			return PLAYER_TWO;
	}
	
	return 0;
}


int cp(board_type *board)
{
	return board->cp;
}