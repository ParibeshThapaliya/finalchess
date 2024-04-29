#include "Player.h"
#include <stdlib.h>

// Function to create a player
struct Player* create_player(enum PlayerColor color, int isComputer) {
    // Allocate memory for the player structure
    struct Player* player = (struct Player*)malloc(sizeof(struct Player));
    if (player == NULL) {
        // Memory allocation failed
        return NULL;
    }

    // Initialize player color and isComputer flag
    player->color = color;
    player->isComputer = isComputer;

    return player;
}
