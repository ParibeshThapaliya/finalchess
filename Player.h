#ifndef PLAYER_H
#define PLAYER_H

// Enumeration for player color
enum PlayerColor {
    WHITE,
    BLACK
} ;

// Structure definition for Player
struct Player {
    // Player color
    enum PlayerColor color;
    // Flag to indicate whether the player is a computer
    int isComputer;
} ;

// Function to create a player
struct Player* create_player(enum PlayerColor color, int isComputer);

#endif /* PLAYER_H */
