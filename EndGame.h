#ifndef ENDGAME_H
#define ENDGAME_H

#include "Board.h"
#include "Game.h"
#include "CheckMove.h"

// Function declarations for checking game end conditions
bool is_in_check(struct Board *board, struct Player *player);
bool is_checkmate(struct Board *board, struct Player *player);
bool is_stalemate(struct Board *board, struct Player *player);

#endif /* ENDGAME_H */
