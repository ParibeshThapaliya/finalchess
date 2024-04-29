#define _CRT_SECURE_NO_WARNINGS

#include "Log.h"

void init_board_list(struct BoardList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}
int index_to_letter(int number)
{
    return 'a' + number;
}

void insert_board(struct BoardList *list, struct Board *board)
{
    // Create a new BoardNode
    struct BoardNode *newNode = (struct BoardNode *)malloc(sizeof(struct BoardNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Assign the board to the new node
    newNode->board = *board;
    newNode->next = NULL;

    // If the list is empty, set the new node as both head and tail
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        // Otherwise, append the new node to the end of the list
        list->tail->next = newNode;
        list->tail = newNode;
    }
    FILE *filePointer;
    filePointer = fopen("../bin/log.txt", "a");
    int xi = newNode->board.lastMove.start.x;
    int yi = newNode->board.lastMove.start.y;
    int xf = newNode->board.lastMove.end.x;
    int yf = newNode->board.lastMove.end.y;
    list->length++;
    fprintf(filePointer, "move %d : %c%d to %c%d\n", list->length,
            index_to_letter(xi), yi + 1, index_to_letter(xf), yf + 1);
    fclose(filePointer);
}

void undo_move(struct BoardList *list)
{
    if (list->head == NULL)
    {
        fprintf(stderr, "Error: Attempting to delete from an empty list\n");
        return;
    }

    // Delete the last node
    struct BoardNode *current = list->head;
    struct BoardNode *prev = NULL;
    while (current->next != NULL)
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        // Only one node in the list
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        // More than one node in the list
        prev->next = NULL;
        free(current);
        list->tail = prev;
    }
    list->length--;
}

void clear_board_list(struct BoardList *list)
{
    while (list->head != NULL)
    {
        undo_move(list);
    }
}
