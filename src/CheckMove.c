#define _CRT_SECURE_NO_WARNINGS

#include "CheckMove.h"
#include <stdlib.h>

bool check_move_pawn(struct Board *board, struct Piece *piece, struct Move *move)
{
    int start_x = move->start.x;
    int start_y = move->start.y;
    int end_x = move->end.x;
    int end_y = move->end.y;

    // Check if the move is within the board bounds
    if (start_x < 0 || start_x >= 8 || start_y < 0 || start_y >= 8 || end_x < 0 || end_x >= 8 || end_y < 0 || end_y >= 8)
    {
        return false;
    }

    // Check if the pawn is moving forward
    if (piece->color == BLACK)
    {
        if (end_y >= start_y)
        {
            return false; // Black pawns can only move forward
        }
    }
    else
    {
        if (end_y <= start_y)
        {
            return false; // White pawns can only move forward
        }
    }

    // Check if the pawn is moving two squares from its initial position
    if (piece->color == BLACK)
    {
        if (start_y == 6 && end_y == start_y - 2)
        {
            return true; // Black pawns can move two squares only from the starting position
        }
    }
    else
    {
        if (start_y == 1 && end_y == start_y + 2)
        {
            return true; // White pawns can move two squares only from the starting position
        }
    }

    // Check if the pawn is moving one square forward
    if (piece->color == BLACK)
    {
        if (end_y != start_y - 1)
        {
            return false;
        }
    }
    else
    {
        if (end_y != start_y + 1)
        {
            return false;
        }
    }
    // en pasant
    if (board->lastMove.start.x>=0&&board->lastMove.start.x<=7) {
        struct Move prevMove = board->lastMove;
        struct Piece lastpeice = *board->squares[prevMove.end.y][prevMove.end.x];
        int diffy = abs(prevMove.start.y - prevMove.end.y);
        int diffx = abs(prevMove.end.x - move->start.x);
        int preMovex = prevMove.end.x;
        // pawns are on the same y , last pawn moved two, and pawn ends in the same x and the distance is 1

        // Check if the pawn is capturing diagonally
        if (abs(end_x - start_x) == 1 && abs(end_y - start_y) == 1)
        { // enpassant
            if (move->start.y == prevMove.end.y && diffy == 2 && move->end.x == preMovex && diffx == 1 &&
                lastpeice.color != piece->color && lastpeice.type == PAWN && board->squares[end_y][end_x] == NULL)
            {
                board->squares[prevMove.end.y][prevMove.end.x] = NULL;

                return true;
            }
            // Check if there is a piece of the opposite color to capture
            else if (board->squares[end_y][end_x] == NULL || board->squares[end_y][end_x]->color == piece->color)
            {
                return false; // No piece to capture or same color piece
            }
            else
            {
                if (end_y == 0 || end_y == 7)
                {
                    piece->type = promotion();
                }
                return true;
            }
        }
    }

    // Check if the destination square is empty
    if (board->squares[end_y][end_x] != NULL)
    {
        return false; // Destination square is not empty
    }

    if (end_x != start_x)
    {
        return false;
    }
    if (end_y == 0 || end_y == 7)
    {

        piece->type = promotion();
    }
    return true;
}
enum PieceType promotion()
{
    char type;
    printf("Enter the what you want the pawn to be promoted to Q,N,R,P,B ");
    scanf("%c", &type);
    switch (tolower(type))
    {
    case 'q':
        return QUEEN;
        break;
    case 'n':
        return KNIGHT;
        break;
    case 'b':
        return BISHOP;
        break;
    case 'r':
        return ROOK;
        break;
    default:
        return PAWN;
    }
    return QUEEN;
}
bool check_move_knight(struct Board *board, struct Piece *piece, struct Move *move)
{
    int start_x = move->start.x;
    int start_y = move->start.y;
    int end_x = move->end.x;
    int end_y = move->end.y;

    // Check if the move is within the board bounds
    if (end_y < 0 || end_y >= 8 || end_x < 0 || end_x >= 8)
    {
        return false;
    }

    // Check if the destination square is occupied by own piece
    if (board->squares[end_y][end_x] != NULL && board->squares[end_y][end_x]->color == piece->color)
    {
        return false;
    }

    // Check if the move is a valid knight's move (L-shape)
    int dx = abs(end_x - start_x);
    int dy = abs(end_y - start_y);
    if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
    {
        return true;
    }

    return false;
}

bool check_move_bishop(struct Board *board, struct Piece *piece, struct Move *move)
{
    int start_x = move->start.x;
    int start_y = move->start.y;
    int end_x = move->end.x;
    int end_y = move->end.y;

    // Check if the move is within the board bounds
    if (end_y < 0 || end_y >= 8 || end_x < 0 || end_x >= 8)
    {
        return false;
    }

    // Check if the destination square is occupied by own piece
    if (board->squares[end_y][end_x] != NULL && board->squares[end_y][end_x]->color == piece->color)
    {
        return false;
    }

    // Check if the move is along a diagonal
    int dx = abs(end_x - start_x);
    int dy = abs(end_y - start_y);
    if (dx != dy)
    {
        return false; // Not along a diagonal
    }

    // Check if there are any obstructing pieces along the diagonal path
    int x_dir = (end_x > start_x) ? 1 : -1;
    int y_dir = (end_y > start_y) ? 1 : -1;
    int x = start_x + x_dir;
    int y = start_y + y_dir;
    while (x != end_x && y != end_y)
    {
        if (board->squares[y][x] != NULL)
        {
            return false; // Obstructed by another piece
        }
        x += x_dir;
        y += y_dir;
    }

    return true;
}

bool check_move_rook(struct Board *board, struct Piece *piece, struct Move *move)
{
    int start_x = move->start.x;
    int start_y = move->start.y;
    int end_x = move->end.x;
    int end_y = move->end.y;

    // Check if the move is within the board bounds
    if (end_y < 0 || end_y >= 8 || end_x < 0 || end_x >= 8)
    {
        return false;
    }

    // Check if the destination square is occupied by own piece
    if (board->squares[end_y][end_x] != NULL && board->squares[end_y][end_x]->color == piece->color)
    {
        return false;
    }

    // Check if the move is along a row or column
    if (start_x != end_x && start_y != end_y)
    {
        return false; // Not along a row or column
    }

    // Check if there are any obstructing pieces along the row or column path
    if (start_x == end_x)
    { // Moving along a column
        int y_dir = (end_y > start_y) ? 1 : -1;
        int y = start_y + y_dir;
        while (y != end_y)
        {
            if (board->squares[y][start_x] != NULL)
            {
                return false; // Obstructed by another piece
            }
            y += y_dir;
        }
    }
    else
    { // Moving along a row
        int x_dir = (end_x > start_x) ? 1 : -1;
        int x = start_x + x_dir;
        while (x != end_x)
        {
            if (board->squares[start_y][x] != NULL)
            {
                return false; // Obstructed by another piece
            }
            x += x_dir;
        }
    }
    if (move->start.x == 0)
    {
        if (piece->color == BLACK)
        {
            board->black_can_castle_queenside = false;
        }
        else
        {
            board->white_can_castle_queenside = false;
        }
    }
    else if (move->start.x == 7)
    {
        if (piece->color == BLACK)
        {
            board->black_can_castle_kingside = false;
        }
        else
        {
            board->white_can_castle_kingside = false;
        }
    }

    return true;
}

bool check_move_queen(struct Board *board, struct Piece *piece, struct Move *move)
{
    // A queen's move is essentially a combination of rook and bishop moves
    return check_move_rook(board, piece, move) || check_move_bishop(board, piece, move);
}

bool check_move_king(struct Board *board, struct Piece *piece, struct Move *move)
{
    // Starting and ending positions of the move
    int start_x = move->start.x;
    int start_y = move->start.y;
    int end_x = move->end.x;
    int end_y = move->end.y;

    // Check if the move is within the board bounds
    if (end_x < 0 || end_x >= 8 || end_y < 0 || end_y >= 8)
    {
        return false;
    }

    // Calculate the absolute difference in x and y coordinates
    int dx = abs(end_x - start_x);
    int dy = abs(end_y - start_y);
    // castle
    bool commenceCastle = true;
    if (move->end.x == 0)
    {
        if (piece->color == BLACK && board->black_can_castle_queenside)
        {
            for (int i = 1; i < 4; i++)
            {
                if (board->squares[7][i] != NULL)
                {
                    commenceCastle = false;
                }
                if (commenceCastle)
                {
                    board->squares[7][2] = board->squares[move->start.y][move->start.x];
                    board->squares[7][3] = board->squares[move->end.y][move->end.x];
                    board->squares[move->end.y][move->end.x] = NULL;
                    board->squares[move->start.y][move->start.x] = NULL;
                    return true;
                }
            }
        }
        else if (piece->color == WHITE && board->white_can_castle_queenside)
        {
            for (int i = 0; i < 3; i++)
            {

                if (board->squares[0][i] != NULL)
                {
                    commenceCastle = false;
                }
                if (commenceCastle)
                {
                    board->squares[0][2] = board->squares[move->start.y][move->start.x];
                    board->squares[0][3] = board->squares[move->end.y][move->end.x];
                    board->squares[move->end.y][move->end.x] = NULL;
                    board->squares[move->start.y][move->start.x] = NULL;
                    return true;
                }
            }
        }
    }
    else if (move->end.x == 7)
    {
        if (piece->color == BLACK && board->black_can_castle_kingside)
        {
            for (int i = 5; i < 7; i++)
            {

                if (board->squares[7][i] != NULL)
                {
                    commenceCastle = false;
                }
                if (commenceCastle)
                {
                    board->squares[7][6] = board->squares[move->start.y][move->start.x];
                    board->squares[7][5] = board->squares[move->end.y][move->end.x];
                    board->squares[move->end.y][move->end.x] = NULL;
                    board->squares[move->start.y][move->start.x] = NULL;
                    return true;
                }
            }
        }
        else if (piece->color == WHITE && board->white_can_castle_kingside)
        {
            for (int i = 5; i < 7; i++)
            {
                if (board->squares[0][i] != NULL)
                {
                    commenceCastle = false;
                }
            }
            if (commenceCastle)
            {
                board->squares[0][6] = board->squares[move->start.y][move->start.x];
                board->squares[0][5] = board->squares[move->end.y][move->end.x];
                board->squares[move->end.y][move->end.x] = NULL;
                board->squares[move->start.y][move->start.x] = NULL;
                return true;
            }
        }
    }

    // The king can move to any adjacent square (including diagonals) within the board
    if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1) || (dx == 1 && dy == 1))
    {
        // Check if the destination square is empty or occupied by an opponent's piece
        if (board->squares[end_y][end_x] == NULL || board->squares[end_y][end_x]->color != piece->color)
        {
            if (piece->color == WHITE)
            {
                board->white_can_castle_kingside = false;
                board->white_can_castle_queenside = false;
            }
            else
            {
                board->black_can_castle_kingside = false;
                board->black_can_castle_queenside = false;
            }

            return true;
        }
    }

    return false;
}

bool checked_after_move(struct Board *board, struct Move *move, struct Player *player)
{
    // Make a copy of the current board
    struct Board copied_board;
    copy_board(board, &copied_board);

    // Perform the move on the copied board
    move_piece(&copied_board, move);

    // Check if the player is in check after the move
    return is_in_check(&copied_board, player);
}
bool is_legal_move(struct Board *board, struct Piece *piece, struct Move *move)
{
    switch (piece->type)
    {
    case PAWN:
        return check_move_pawn(board, piece, move);
    case KNIGHT:
        return check_move_knight(board, piece, move);
    case BISHOP:
        return check_move_bishop(board, piece, move);
    case ROOK:
        return check_move_rook(board, piece, move);
    case QUEEN:
        return check_move_queen(board, piece, move);
    case KING:
        return check_move_king(board, piece, move);
    default:
        return false;
    }
}
