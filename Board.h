#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Player.h"

// Piece type enumeration definition
enum PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

struct Piece
{
    // Piece type
    enum PieceType type;
    // Owning player
    enum PlayerColor color;
};

struct Position
{
    // Horizontal coordinate
    int x;
    // Vertical coordinate
    int y;
};

struct Move
{
    // Starting position
    struct Position start;
    // Ending position
    struct Position end;
    int score;
};

struct Board
{

    // Two-dimensional array representing pieces on each position of the board
    struct Piece *squares[8][8];
    // Flags to track whether castling is possible for each player
    bool white_can_castle_kingside;
    bool white_can_castle_queenside;
    bool black_can_castle_kingside;
    bool black_can_castle_queenside;
    struct Move lastMove;
};

// Function to initialize the board
void init_board(struct Board *board);

// Function to copy the board
void copy_board(struct Board *src, struct Board *dest);

// Function to print the current board position
void print_board(struct Board *board);

// Function to create a piece with the given type and color
struct Piece *create_piece(enum PieceType type, enum PlayerColor color);

// Function to move a piece on the board based on user input
bool move_piece(struct Board *board, struct Move *move);

#endif /* BOARD_H */
