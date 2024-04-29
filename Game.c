#include "Game.h"

void init_game(struct Game* game, struct Player player1, struct Player player2) {
    // initial board
    init_board(&(game->board));

    // initial player
    game->player1 = player1;
    game->player2 = player2;

    game->current_player = &(game->player1);

    // initial log
    init_board_list(&(game->log));
}


void switch_players(struct Game* game) {
    if (game->current_player == &(game->player1)) {
        game->current_player = &(game->player2);
    }
    else {
        game->current_player = &(game->player1);
    }
}
