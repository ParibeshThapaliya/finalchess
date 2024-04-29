#ifndef CHECKMOVE_H
#define CHECKMOVE_H

#include "Board.h"

// Function declarations for checking moves
bool check_move_pawn(struct Board *board, struct Piece *piece, struct Move *move);
bool check_move_knight(struct Board *board, struct Piece *piece, struct Move *move);
bool check_move_bishop(struct Board *board, struct Piece *piece, struct Move *move);
bool check_move_rook(struct Board *board, struct Piece *piece, struct Move *move);
bool check_move_queen(struct Board *board, struct Piece *piece, struct Move *move);
bool check_move_king(struct Board *board, struct Piece *piece, struct Move *move);
bool special_moves(struct Board *board, struct Piece *piece, struct Move *move);
bool is_legal_move(struct Board *board, struct Piece *piece, struct Move *move);
enum PieceType promotion();
bool checked_after_move(struct Board *board, struct Move *move, struct Player *player);
#endif /* CHECKMOVE_H */
