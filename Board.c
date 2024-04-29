#include "Board.h"
struct Piece *create_piece(enum PieceType type, enum PlayerColor color)
{
    // Allocate memory for the piece structure
    struct Piece *piece = (struct Piece *)malloc(sizeof(struct Piece));
    if (piece == NULL)
    {
        // Memory allocation failed
        return NULL;
    }

    // Initialize piece type and owner
    piece->type = type;
    piece->color = color;

    return piece;
}

void init_board(struct Board *board)
{
    // Initialize all squares on the board to NULL
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            board->squares[i][j] = NULL;
        }
    }

    // Set up the initial position of pieces for both players

    // White pieces
    // Pawns
    for (int j = 0; j < 8; ++j)
    {
        board->squares[1][j] = create_piece(PAWN, WHITE);
    }

    // Rooks
    board->squares[0][0] = create_piece(ROOK, WHITE);
    board->squares[0][7] = create_piece(ROOK, WHITE);

    // Knights
    board->squares[0][1] = create_piece(KNIGHT, WHITE);
    board->squares[0][6] = create_piece(KNIGHT, WHITE);

    // Bishops
    board->squares[0][2] = create_piece(BISHOP, WHITE);
    board->squares[0][5] = create_piece(BISHOP, WHITE);

    // Queen
    board->squares[0][3] = create_piece(QUEEN, WHITE);

    // King
    board->squares[0][4] = create_piece(KING, WHITE);

    // Black pieces
    // Pawns
    for (int j = 0; j < 8; ++j)
    {
        board->squares[6][j] = create_piece(PAWN, BLACK);
    }

    // Rooks
    board->squares[7][0] = create_piece(ROOK, BLACK);
    board->squares[7][7] = create_piece(ROOK, BLACK);

    // Knights
    board->squares[7][1] = create_piece(KNIGHT, BLACK);
    board->squares[7][6] = create_piece(KNIGHT, BLACK);

    // Bishops
    board->squares[7][2] = create_piece(BISHOP, BLACK);
    board->squares[7][5] = create_piece(BISHOP, BLACK);

    // Queen
    board->squares[7][3] = create_piece(QUEEN, BLACK);

    // King
    board->squares[7][4] = create_piece(KING, BLACK);
}

void copy_board(struct Board *src, struct Board *dest)
{
    // Copy piece information from source board to destination board
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (src->squares[i][j] != NULL)
            {
                dest->squares[i][j] = create_piece(src->squares[i][j]->type, src->squares[i][j]->color);
            }
            else
            {
                dest->squares[i][j] = NULL;
            }
        }
    }
}

// Function to print the current board position
void print_board(struct Board *board)
{
    // Print the column labels
    printf("  +----+----+----+----+----+----+----+----+\n");

    // Iterate through each row
    for (int i = 0; i < 8; ++i)
    {
        // Print the row number
        printf("%d ", 8 - i);

        // Iterate through each column
        for (int j = 0; j < 8; ++j)
        {
            // Print the piece symbol or empty square
            if (board->squares[7 - i][j] != NULL)
            {
                switch (board->squares[7 - i][j]->type)
                {
                case KING:
                    if (board->squares[7 - i][j]->color == WHITE)
                        printf("| wk ");
                    else
                        printf("| bk ");
                    break;
                case QUEEN:
                    if (board->squares[7 - i][j]->color == WHITE)
                        printf("| wq ");
                    else
                        printf("| bq ");
                    break;
                case ROOK:
                    if (board->squares[7 - i][j]->color == WHITE)
                        printf("| wr ");
                    else
                        printf("| br ");
                    break;
                case BISHOP:
                    if (board->squares[7 - i][j]->color == WHITE)
                        printf("| wb ");
                    else
                        printf("| bb ");
                    break;
                case KNIGHT:
                    if (board->squares[7 - i][j]->color == WHITE)
                        printf("| wn ");
                    else
                        printf("| bn ");
                    break;
                case PAWN:
                    if (board->squares[7 - i][j]->color == WHITE)
                        printf("| wp ");
                    else
                        printf("| bp ");
                    break;
                }
            }
            else
            {
                printf("|    ");
            }
        }

        // Print the column labels
        printf("|\n  +----+----+----+----+----+----+----+----+\n");
    }

    // Print the column labels
    printf("    a    b    c    d    e    f    g    h\n");
}

bool move_piece(struct Board *board, struct Move *move)
{
    // Check if the starting and ending positions are within the board boundaries
    if (move->start.x < 0 || move->start.x >= 8 || move->start.y < 0 || move->start.y >= 8 ||
        move->end.x < 0 || move->end.x >= 8 || move->end.y < 0 || move->end.y >= 8)
    {
        printf("Invalid move: positions out of bounds.\n");
        return false;
    }

    // Get the piece at the starting position
    struct Piece *piece = board->squares[move->start.y][move->start.x];

    // Check if there is a piece at the starting position
    if (piece == NULL)
    {
        printf("Invalid move: no piece at the starting position.\n");
        return false;
    }

    // Check if the piece can legally move to the ending position (implementation omitted)
    // If the move is legal, update the board
    board->squares[move->end.y][move->end.x] = piece;
    board->squares[move->start.y][move->start.x] = NULL;

    return true;
}