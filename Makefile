CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
OBJ_DIR = bin
OBJ = $(OBJ_DIR)/AI.o $(OBJ_DIR)/Board.o $(OBJ_DIR)/CheckMove.o $(OBJ_DIR)/EndGame.o $(OBJ_DIR)/Log.o $(OBJ_DIR)/main.o $(OBJ_DIR)/Player.o $(OBJ_DIR)/Game.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OBJ_DIR)/chess

$(OBJ_DIR)/AI.o: $(SRC_DIR)/AI.c $(SRC_DIR)/AI.h $(SRC_DIR)/Board.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Board.o: $(SRC_DIR)/Board.c $(SRC_DIR)/Board.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/CheckMove.o: $(SRC_DIR)/CheckMove.c $(SRC_DIR)/CheckMove.h $(SRC_DIR)/Board.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/EndGame.o: $(SRC_DIR)/EndGame.c $(SRC_DIR)/EndGame.h $(SRC_DIR)/Board.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Log.o: $(SRC_DIR)/Log.c $(SRC_DIR)/Log.h $(SRC_DIR)/Board.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/Board.h $(SRC_DIR)/Player.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Player.o: $(SRC_DIR)/Player.c $(SRC_DIR)/Player.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Game.o: $(SRC_DIR)/Game.c $(SRC_DIR)/Game.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ_DIR)/chess $(OBJ_DIR)/*.o
tar:
	tar -czvf Chess_Alpha_src.tar.gz README INSTALL COPYRIGHT bin doc src Makefile
test:
	./bin/chess
