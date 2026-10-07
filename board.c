#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "board.h"

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

void board_push(board_t *b, int line, int row, char ctn) {
  int top = ++(b->tiles[GRIDWIDTH * line + row].top);
  b->tiles[GRIDWIDTH * line + row].stack[top] = ctn;
}

char board_pop(board_t *b, int line, int row) {
  assert(b->tiles[GRIDWIDTH * line + row].top > -1);
  int top = (b->tiles[GRIDWIDTH * line + row].top)--;
  return b->tiles[GRIDWIDTH * line + row].stack[top];
}

int board_height(board_t *b, int line, int row) {
  return b->tiles[GRIDWIDTH * line + row].top + 1;
}

char board_top(board_t *b, int line, int row) {
  int top = (b->tiles[GRIDWIDTH * line + row].top);
  return b->tiles[GRIDWIDTH * line + row].stack[top];
}

char board_peek(board_t *b, int line, int row, int pos) { // pos = 0 => top
  int index = b->tiles[GRIDWIDTH * line + row].top - pos;
  assert(index > -1);
  return b->tiles[GRIDWIDTH * line + row].stack[index];
}

board_t board_init(board_t *b, int trapped[GRIDHEIGHT][GRIDWIDTH]) {
  for (int line = 0; line < GRIDHEIGHT; line++) {
    for (int row = 0; row < GRIDWIDTH; row++) {
      if (trapped[line][row] == 1) {
        b->tiles[GRIDWIDTH * line + row].trapped = true;
      } else {
        b->tiles[GRIDWIDTH * line + row].trapped = false;
      }
      b->tiles[GRIDWIDTH * line + row].top = -1;
    }
  }
}


void cell_print(board_t *b, int line, int row, int slice) {
  cell_t c = b->tiles[GRIDWIDTH * line + row];
  int size = c.top + 1;
  // top, down, left and right border characters
  char t;
  char d;
  char l;
  char r;
  if (c.trapped) {
    t = 'v';
    d = '^';
    l = '>';
    r = '<';
  } else {
    t = '-';
    d = '-';
    l = '|';
    r = '|';
  }
  switch (slice) {
  case 0:
    printf(" %c%c%c ", t, t, t);
    break;
  case 1:
    if (size == 0) {
      printf("%c   %c", l, r);
    } else {
      char v = c.stack[c.top];
      printf("%c%c%c%c%c", l, v, v, v, r);
    }
    break;
  case 2:
    char v;
    char v1;
    char v2;
    char v3;
    switch (size) {
    case 0:
      printf("%c   %c", l, r);
      break;
    case 1:
      v = c.stack[c.top];
      printf("%c%c%c%c%c", l, v, v, v, r);
      break;
    case 2:
      v = c.stack[c.top - 1] + 'a' - 'A';
      printf("%c%c%c%c%c", l, v, v, v, r);
      break;
    case 3:
      v1 = c.stack[c.top - 1] + 'a' - 'A';
      v2 = c.stack[c.top - 2] + 'a' - 'A';
      printf("%c%c %c%c", l, v1, v2, r);
      break;
    default:
      v1 = c.stack[c.top - 1] + 'a' - 'A';
      v2 = c.stack[c.top - 2] + 'a' - 'A';
      v3 = c.stack[c.top - 3] + 'a' - 'A';
      printf("%c%c%c%c%c", l, v1, v2, v3, r);
      break;
    }
    break;
  default:
    if (size == 0) {
      printf(" %c%c%c ", d, d, d);
    } else {
      printf(" %c%d%c ", d, size, d);
    }
    break;
  }
}

void board_print(
    board_t *b,
    int highlited_line) { // if highlited_line is -1 then nothing is selected
                          /*This function takes a maximum of 26 rows*/
  printf("      ");
  printf("START\n\n");
  for (int line = 0; line <= GRIDHEIGHT; line++) {
    if (line == 0) {
      printf("      ");
      for (int row = 0; row < GRIDWIDTH; row++) {
        printf(" row   ");
      }
      printf("\n");
      printf("      ");
      for (int row = 0; row < GRIDWIDTH; row++) {
        printf("   %c   ", 'a' + row);
      }
    } else {
      char h = ' ';
      if (line == highlited_line)
        h = '>';
      for (int slice = 0; slice < 4; slice++) {
        switch (slice) {
        case 1:
          printf("line%c ", h);
          break;
        case 2:
          printf("  %d %c ", line, h);
          break;
        default:
          printf("    %c ", h);
          break;
        }
        for (int row = 0; row < GRIDWIDTH; row++) {
          cell_print(b, line, row, slice);
          printf("  ");
        }
        printf("\n");
      }
    }
  }
}
