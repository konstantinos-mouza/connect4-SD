#ifndef __AI_H
#define __AI_H

#include "gameplay.h"

int getRandomPlayerMove(board_type *board);

int getStrength(board_type *board);

int minValue(board_type *board, int ply);

int maxValue(board_type *board, int ply);

int getReasonedMove(board_type *board);


#endif