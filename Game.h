#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Log.h"

struct Game {
    struct Board board;
    struct Player player1;
    struct Player player2;
    struct Player* current_player;
    struct BoardList log;
};

void init_game(struct Game* game, struct Player player1, struct Player player2);
void switch_players(struct Game* game);

#endif /* GAME_H */
