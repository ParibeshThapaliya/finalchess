#include "AI.h"


const int POSITION_WHITE_PAWN[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10, -20, -20, 10, 10, 5,
    5, -5, -10, 0, 0, -10, -5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, 5, 10, 25, 25, 10, 5, 5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0, 0, 0, 0, 0, 0, 0, 0
};

const int POSITION_WHITE_KNIGHT[64] = {
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20, 0, 5, 5, 0, -20, -40,
    -30, 5, 10, 15, 15, 10, 5, -30,
    -30, 0, 15, 20, 20, 15, 0, -30,
    -30, 5, 15, 20, 20, 15, 5, -30,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -40, -20, 0, 0, 0, 0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50
};

const int POSITION_WHITE_BISHOP[64] = {
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10, 5, 0, 0, 0, 0, 5, -10,
    -10, 10, 10, 10, 10, 10, 10, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 5, 5, 10, 10, 5, 5, -10,
    -10, 0, 5, 10, 10, 5, 0, -10,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -20, -10, -10, -10, -10, -10, -10, -20
};

const int POSITION_WHITE_ROOK[64] = {
    0, 0, 0, 5, 5, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    5, 10, 10, 10, 10, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0
};

const int POSITION_WHITE_QUEEN[64] = {
    -20, -10, -10, -5, -5, -10, -10, -20,
    -10, 0, 5, 0, 0, 0, 0, -10,
    -10, 5, 5, 5, 5, 5, 0, -10,
    0, 0, 5, 5, 5, 5, 0, -5,
    -5, 0, 5, 5, 5, 5, 0, -5,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20
};

const int POSITION_WHITE_KING[64] = {
    20, 30, 10, 0, 0, 10, 30, 20,
    20, 20, 0, 0, 0, 0, 20, 20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30
};

// Black pieces position scores
const int POSITION_BLACK_PAWN[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5, 5, 10, 25, 25, 10, 5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, -5, -10, 0, 0, -10, -5, 5,
    5, 10, 10, -20, -20, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0
};

const int POSITION_BLACK_KNIGHT[64] = {
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20, 0, 0, 0, 0, -20, -40,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -30, 5, 15, 20, 20, 15, 5, -30,
    -30, 0, 15, 20, 20, 15, 0, -30,
    -30, 5, 10, 15, 15, 10, 5, -30,
    -40, -20, 0, 5, 5, 0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50
};

const int POSITION_BLACK_BISHOP[64] = {
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 10, 10, 5, 0, -10,
    -10, 5, 5, 10, 10, 5, 5, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 10, 10, 10, 10, 10, 10, -10,
    -10, 5, 0, 0, 0, 0, 5, -10,
    -20, -10, -10, -10, -10, -10, -10, -20
};

const int POSITION_BLACK_ROOK[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10, 10, 10, 10, 10, 5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 5, 5, 0, 0, 0
};

const int POSITION_BLACK_QUEEN[64] = {
    -20, -10, -10, -5, -5, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -5, 0, 5, 5, 5, 5, 0, -5,
    0, 0, 5, 5, 5, 5, 0, -5,
    -10, 5, 5, 5, 5, 5, 0, -10,
    -10, 0, 5, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20
};

const int POSITION_BLACK_KING[64] = {
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    20, 20, 0, 0, 0, 0, 20, 20,
    20, 30, 10, 0, 0, 10, 30, 20
};

int evaluate_board(struct Board* board) {
    int score = 0;

    // Loop through all squares on the board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            struct Piece* piece = board->squares[i][j];
            if (piece != NULL) {
                // Add piece value
                switch (piece->type) {
                case PAWN:
                    score += (piece->color == WHITE) ? 100 : -100;
                    score += (piece->color == WHITE) ? POSITION_WHITE_PAWN[i * 8 + j] : -POSITION_BLACK_PAWN[i * 8 + j];
                    break;
                case KNIGHT:
                    score += (piece->color == WHITE) ? 320 : -320;
                    score += (piece->color == WHITE) ? POSITION_WHITE_KNIGHT[i * 8 + j] : -POSITION_BLACK_KNIGHT[i * 8 + j];
                    break;
                case BISHOP:
                    score += (piece->color == WHITE) ? 330 : -330;
                    score += (piece->color == WHITE) ? POSITION_WHITE_BISHOP[i * 8 + j] : -POSITION_BLACK_BISHOP[i * 8 + j];
                    break;
                case ROOK:
                    score += (piece->color == WHITE) ? 500 : -500;
                    score += (piece->color == WHITE) ? POSITION_WHITE_ROOK[i * 8 + j] : -POSITION_BLACK_ROOK[i * 8 + j];
                    break;
                case QUEEN:
                    score += (piece->color == WHITE) ? 900 : -900;
                    score += (piece->color == WHITE) ? POSITION_WHITE_QUEEN[i * 8 + j] : -POSITION_BLACK_QUEEN[i * 8 + j];
                    break;
                case KING:
                    score += (piece->color == WHITE) ? 20000 : -20000;
                    score += (piece->color == WHITE) ? POSITION_WHITE_KING[i * 8 + j] : -POSITION_BLACK_KING[i * 8 + j];
                    break;
                }
            }
        }
    }

    return score;
}

// Function to find the best move
struct Move best_move_search(struct Board* board, bool maximizing_player) {
    // Initialize the best move
    struct Move best_move;
    best_move.score = maximizing_player ? INT_MIN : INT_MAX;

    // Loop through all board positions
    for (int from_y = 0; from_y < 8; ++from_y) {
        for (int from_x = 0; from_x < 8; ++from_x) {
            // If there is a piece at this position owned by the current player
            if (board->squares[from_y][from_x] != NULL && board->squares[from_y][from_x]->color == (maximizing_player ? WHITE : BLACK)) {
                // Loop through all possible target positions for this piece
                for (int to_y = 0; to_y < 8; ++to_y) {
                    for (int to_x = 0; to_x < 8; ++to_x) {
                        // Check if the move is valid
                        struct Move move;
                        move.start.x = from_x;
                        move.start.y = from_y;
                        move.end.x = to_x;
                        move.end.y = to_y;

                        // Apply move to a copy of the board
                        struct Board new_board;
                        copy_board(board, &new_board);
                        if (is_legal_move(&new_board, new_board.squares[from_y][from_x], &move)) {
                            // Recursively call alpha_beta_search with decreased depth
                            move_piece(&new_board, &move);
                            int score = evaluate_board(&new_board);
                            // Update best move if needed
                            if ((maximizing_player && score > best_move.score) || (!maximizing_player && score < best_move.score)) {
                                best_move = move;
                                best_move.score = score;
                            }
                        }
                    }
                }
            }
        }
    }

    return best_move;
}
