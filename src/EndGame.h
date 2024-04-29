#ifndef ENDGAME_H
#define ENDGAME_H

#include "Board.h"
#include "Game.h"
#include "CheckMove.h"

// Function declarations for checking game end conditions
bool is_in_check(struct Game *game, struct Player *player);
bool is_checkmate(struct Game *game, struct Player *player);
bool is_stalemate(struct Game *game, struct Player *player);

#endif /* ENDGAME_H */
