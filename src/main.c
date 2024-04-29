#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "AI.h"
#include "Board.h"
#include "Game.h"
#include "CheckMove.h"
#include "EndGame.h"
#include "Log.h"
#include "Player.h"

// Function to convert a letter to its corresponding index (0-7)
int letter_to_index(char letter)
{
    return tolower(letter) - 'a';
}

struct Move get_user_move()
{
    struct Move move;

    // Get starting and ending position from user
    printf("Enter the starting and ending position (format: a7 a6): ");
    char start_letter, end_letter;
    int start_number, end_number;
    scanf(" %c%d %c%d", &start_letter, &start_number, &end_letter, &end_number);
    move.start.x = letter_to_index(start_letter);
    move.start.y = start_number - 1;

    move.end.x = letter_to_index(end_letter);
    move.end.y = end_number - 1;

    return move;
}

int main(void)
{
    FILE *filePointer;
    filePointer = fopen("../bin/log.txt", "w");

    if (filePointer == NULL)
    {

        printf("Unable to open the file.\n");
        return -1;
    }
    fprintf(filePointer, "GAME START\n");
    fclose(filePointer);
    // choose game mode
    printf("Welcome to Chess Game!\n");
    printf("Please choose the game mode:\n");
    printf("1. Human vs Human\n");
    printf("2. Human vs AI\n");
    printf("3. AI vs AI\n");

    int choice;
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    struct Game game;
    struct Player player1, player2;
    struct Move move;
    struct Piece *piece;

    // initial player color
    player1.color = WHITE;
    player2.color = BLACK;

    // initial game
    switch (choice)
    {
    case 1:
        // pvp
        printf("Human vs Human mode selected.\n");
        player1.isComputer = false;
        player2.isComputer = false;
        break;
    case 2:
        // pvc
        printf("Human vs AI mode selected.\n");
        player1.isComputer = false;
        player2.isComputer = true;
        break;
    case 3:
        // cvc
        printf("AI vs AI mode selected.\n");
        player1.isComputer = true;
        player2.isComputer = true;
        break;
    default:
        printf("Invalid choice. Exiting...\n");
        return 1;
    }
    init_game(&game, player1, player2);
    print_board(&game.board);
    while (true)
    {
        printf("It is player1's turn:\n");

        if (player1.isComputer)
        {
            move = best_move_search(&game.board, true);
        }
        else
        {
            do
            {
                move = get_user_move();

                piece = game.board.squares[move.start.y][move.start.x];
            } while (piece == NULL || !is_legal_move(&game.board, piece, &move) || piece->color != player1.color || is_in_check(&game.board, &player1));
        }
        move_piece(&game.board, &move);
        game.board.lastMove = move;
        insert_board(&game.log, &game.board);
        print_board(&game.board);
        if (is_checkmate(&game.board, &player2))
        {
            printf("Player1 Win!\n");
            break;
        }
        else if (is_stalemate(&game.board, &player2))
        {
            printf("Stalemate!\n");
            break;
        }
        switch_players(&game);
        printf("It is player2's turn:\n");
        if (player2.isComputer)
        {
            move = best_move_search(&game.board, false);
        }
        else
        {
            do
            {
                move = get_user_move();
                piece = game.board.squares[move.start.y][move.start.x];
            } while (piece == NULL || !is_legal_move(&game.board, piece, &move) || piece->color != player2.color || is_in_check(&game.board, &player2));
        }

        move_piece(&game.board, &move);
        game.board.lastMove = move;
        insert_board(&game.log, &game.board);
        print_board(&game.board);
        if (is_checkmate(&game.board, &player1))
        {
            printf("Player2 Win!\n");
            break;
        }
        else if (is_stalemate(&game.board, &player1))
        {
            printf("Stalemate!\n");
            break;
        }
        switch_players(&game);
    }

    filePointer = fopen("../bin/log.txt", "a");

    if (filePointer == NULL)
    {

        printf("Unable to open the file.\n");
        return -1;
    }
    fprintf(filePointer, "GAME END\n");
    fclose(filePointer);
    return 0;
}
