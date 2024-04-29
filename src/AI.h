#ifndef AI_H
#define AI_H

#include "Board.h"
#include "CheckMove.h"
#include "Game.h"
#include <limits.h>

// Alpha Beta search function definition
struct Move best_move_search(struct Board *board, bool maximizing_player);

// Function to evaluate the position score
int evaluate_board(struct Board *board);

#endif /* AI_H */
