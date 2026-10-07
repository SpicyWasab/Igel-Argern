#ifndef BOARD_H
#define BOARD_H

#define GRIDHEIGHT 3
#define GRIDWIDTH 3
#define PLAYERCOUNT 2
#define HEDGEHOGS 2

struct cell {
  char stack[PLAYERCOUNT * HEDGEHOGS]; // Uppercase letters
  int top; // index of the first hedgehog; -1 if the tile is empty
  bool trapped;
};
typedef struct cell cell_t;

struct board {
  cell_t tiles[GRIDHEIGHT * GRIDWIDTH];
};
typedef struct board board_t;

void board_push(board_t *b, int line, int row, char ctn);

char board_pop(board_t *b, int line, int row);

int board_height(board_t *b, int line, int row);

char board_top(board_t *b, int line, int row);

char board_peek(board_t *b, int line, int row, int pos);

board_t board_init(board_t *b, int trapped[GRIDHEIGHT][GRIDWIDTH]);


void cell_print(board_t *b, int line, int row, int slice);

void board_print(
    board_t *b,
    int highlited_line);
#endif
