#include "board.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

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

bool board_is_line_empty(board_t *b, int line, int max_row) {
  for (int i = 0; i < max_row; i++) {
    if (board_height(b, line, i) > 0)
      return false;
  }

  return true;
}

bool board_check_trapped(board_t *b, int line, int row) {
  return b->tiles[GRIDWIDTH * line + row].trapped;
}

void board_add_won_hedgehog(board_t *b, int player) {
  b->won_hedgehogs[player]++;
}

bool board_get_won_hedgehogs(board_t *b, int player) {
  return b->won_hedgehogs[player];
}

void board_init(board_t *b, int trapped[GRIDHEIGHT][GRIDWIDTH]) {
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

/*checks the presence of two pieces alike with one on top, but does not check if
 * the coordinates are exact*/
bool board_sandwichable(board_t *b, int line, int row) {
  cell_t c = b->tiles[GRIDWIDTH * line + row];
  int index_base = c.top - 1;
  while (c.stack[index_base] != board_top(b, line, row) && index_base >= 0) {
    index_base--;
  }
  return (index_base >= 0);
}

/*This function supposes sandwiching is possible :  must check first.
It also does not verify if the movement is in range. Uses line indexing starting
at 0*/
void board_sandwich(board_t *b, int line, int row, int line_dest,
                    int row_dest) {
  assert(board_sandwichable(b, line, row));
  cell_t c = b->tiles[GRIDWIDTH * line + row];
  cell_t c_dest = b->tiles[GRIDWIDTH * line_dest + row_dest];
  int index_base = c.top - 1;
  while (c.stack[index_base] != board_top(b, line, row) && index_base >= 0) {
    index_base--;
  }
  assert(index_base >= 0);
  for (int i = 0; i <= c.top - index_base; i++) {
    b->tiles[GRIDWIDTH * line_dest + row_dest].stack[i + c_dest.top + 1] =
        b->tiles[GRIDWIDTH * line + row].stack[i + index_base];
  }
  b->tiles[GRIDWIDTH * line_dest + row_dest].top += c.top - index_base + 1;

  b->tiles[GRIDWIDTH * line + row].top = index_base - 1;
}

void cell_print(board_t *b, int line, int row, int slice) {
  cell_t c = b->tiles[GRIDWIDTH * line + row];
  int size = c.top + 1;
  char t = '-';
  char d = '-';
  char l = '|';
  char r = '|';

  if (c.trapped == 1) {
    t = 'v';
    d = '^';
    l = '>';
    r = '<';
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
    if (size <= 1) {
      printf(" %c%c%c ", d, d, d);
    } else {
      printf(" %c%d%c ", d, size, d);
    }
    break;
  }
}

/*
if highlited_line is -1 then nothing is selected
This function takes a maximum of 26 rows*/
void board_print(board_t *b, int highlited_line) {
  printf("\n");
  for (int line = 0; line <= GRIDHEIGHT; line++) {
    if (line == 0) {
      printf("      START  ");
      for (int row = 1; row < GRIDWIDTH - 1; row++) {
        printf("       ");
      }
      printf("FINISH\n\n");
      printf("      ");
      for (int row = 0; row < GRIDWIDTH; row++) {
        printf(" row   ");
      }
      printf("\n");
      printf("      ");
      for (int row = 0; row < GRIDWIDTH; row++) {
        printf("  %c    ", 'a' + row);
      }
      printf("\n\n");
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
          cell_print(b, line - 1, row, slice);
          printf("  ");
        }
        printf("\n");
      }
    }
  }
  printf("      ");
  for (int row = 0; row < GRIDWIDTH; row++) {
    printf(" row   ");
  }
  printf("\n");
  printf("      ");
  for (int row = 0; row < GRIDWIDTH; row++) {
    printf("  %c    ", 'a' + row);
  }
  printf("\n");
}
