#include "EndGame.h"

bool is_in_check(struct Board* board, struct Player* player) {
    // Get the current player's color
    enum PlayerColor player_color = player->color;

    // Find the king's position
    int king_x = -1, king_y = -1;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            struct Piece* piece = board->squares[y][x];
            if (piece != NULL && piece->type == KING && piece->color == player_color) {
                king_x = x;
                king_y = y;
                break;
            }
        }
        if (king_x != -1 && king_y != -1) {
            break;
        }
    }

    // If king's position is not found, return false
    if (king_x == -1 || king_y == -1) {
        return false;
    }

    // Check if any opponent's piece can capture the king
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            struct Piece* piece = board->squares[y][x];
            if (piece != NULL && piece->color != player_color) {
                struct Move move = { {x, y}, {king_x, king_y} };
                if (is_legal_move(board, piece, &move)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool is_checkmate(struct  Board* board, struct Player* player) {
    // Check if the player is in check
    if (!is_in_check(board, player)) {
        return false; // Not in check, so not checkmate
    }

    // Iterate through all pieces of the current player
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            struct Piece* piece = board->squares[y][x];
            if (piece != NULL && piece->color == player->color) {
                // Try moving each piece to every possible position
                for (int dest_y = 0; dest_y < 8; ++dest_y) {
                    for (int dest_x = 0; dest_x < 8; ++dest_x) {
                        struct Move move = { {x, y}, {dest_x, dest_y} };
                        if (is_legal_move(board, piece, &move)) {
                            // Make a copy of the board and apply the move
                            struct Board temp_board;
                            copy_board(board, &temp_board);
                            move_piece(&temp_board, &move);

                            // If the king is not in check after the move, return false
                            if (!is_in_check(board, player)) {
                                return false; // The player can escape from checkmate
                            }
                        }
                    }
                }
            }
        }
    }

    // If no move can prevent the checkmate, return true
    return true;
}

bool is_stalemate(struct  Board* board, struct Player* player) {
    // Check if the player is in check
    if (is_in_check(board, player)) {
        return false; // If the player is in check, it's not stalemate
    }

    // Iterate through all pieces of the current player
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            struct Piece* piece = board->squares[y][x];
            if (piece != NULL && piece->color == player->color) {
                // Try moving each piece to every possible position
                for (int dest_y = 0; dest_y < 8; ++dest_y) {
                    for (int dest_x = 0; dest_x < 8; ++dest_x) {
                        struct Move move = { {x, y}, {dest_x, dest_y} };
                        if (is_legal_move(board, piece, &move)) {
                            // Make a copy of the board and apply the move
                            struct Board temp_board;
                            copy_board(board, &temp_board);
                            move_piece(&temp_board, &move);

                            // If the player is not in check after the move, return false
                            if (!is_in_check(board, player)) {
                                return false; // The player can make a legal move
                            }
                        }
                    }
                }
            }
        }
    }

    // If no legal move can be made without getting into check, it's stalemate
    return true;
}