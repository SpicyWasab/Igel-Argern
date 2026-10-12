#include "board.h"
#include "input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// const int player_count = 4;

int roll_dice() { return rand() % 6 + 1; }

int main(void) {
  srand(time(NULL));

  int trapped_tiles[GRIDHEIGHT][GRIDWIDTH] = {{0, 0, 1}, {0, 0, 0}, {0, 0, 0}};

  board_t b;

  board_init(&b, trapped_tiles);

  // placing hedgehogs, because the game is a bit boring when there aren't any
  // hedgehogs yet
  for (int i = 0; i < HEDGEHOGSPERPLAYER; i++) {
    board_push(&b, roll_dice() % GRIDHEIGHT, 0, i % PLAYERCOUNT + 'A');
  }

  bool game_over = false;

  while (!game_over) {
    for (int player = 0; player < PLAYERCOUNT; player++) {
      int player_name = player + 65; // 65 is the ascii code for 'A'
      printf("Au tour du joueur %c ! \n", player_name);

      int rolled_line = (roll_dice() - 1) % (GRIDHEIGHT);

      printf("We roll... a %d !\n", rolled_line + 1);

      board_print(&b, rolled_line + 1);
      bool can_move = false;
      for (int row = 0; row < GRIDWIDTH; row++) {
        for (int line = 0; line < GRIDHEIGHT; line++) {
          if (board_top(&b, line, row) == player_name)
            can_move = true;
        }
      }
      bool move_hedgehog = false;
      if (can_move) {
        move_hedgehog = input_move_or_not();
      } else {
        printf("You have no hedgehog to move up or down.\n");
      }

      if (move_hedgehog) {
        char movement[3];
        input_move(movement);
        bool move_ok = false;
        char row = movement[0] - 'A';
        int line = movement[1] - '0' -
                   1; // 0 is not a valid line since they start at 1. We make
                      // this usable by directly applying -1
        char dir = movement[2];

        while (!move_ok) {
          bool passed = true;
          if (row > GRIDWIDTH + 'A' || line >= GRIDHEIGHT || line < 0) {
            printf("This position is out of bounds %d\n", line);
            passed = false;

          } else if (board_height(&b, line, row) < 1) {
            printf("There is no hedgehog here\n");
            passed = false;
          } else if (passed && board_top(&b, line, row) != player_name) {
            printf("You have no hedgehog up here\n");
            passed = false;

          } else if (board_check_trapped(&b, line, row) &&
                     !(board_is_line_empty(&b, line, row))) {
            printf("This hedgehog is trapped\n");
            passed = false;

          } else if (passed &&
                     ((dir == 'T' && line < 1) || (dir == 't' && line < 1) ||
                      (dir == 'B' && line >= GRIDHEIGHT - 1) ||
                      (dir == 'b' && line >= GRIDHEIGHT - 1))) {
            printf("You cannot move there\n");
            passed = false;
          }

          if (passed) {
            move_ok = true;
          } else {
            input_move(movement);
            row = movement[0] - 'A';
            line = movement[1] - '0' - 1;
            dir = movement[2];
          }
        }
        if (dir == 'T' || dir == 't') {
          board_pop(&b, line, row);
          board_push(&b, line - 1, row, player_name);
        } else {
          board_pop(&b, line, row);
          board_push(&b, line + 1, row, player_name);
        }

        // printf("On a sélectionné la row %d et la line %d \n", row, line);

        /*char player_owning_cell = board_top(&b, line, row);

        if(player_owning_cell != player_name) printf("Ce hérisson n'appartient
    pas à votre équipe.\n"); else { printf("Indiquez la direction du
    déplacement (H/B): "); char direction = 'N'; scanf(" %c", &direction);

            if(direction == 'H') {
                if(line == 0) printf("Vous ne pouvez pas vous déplacer vers le
    haut.\n"); else { char hedgehog = board_pop(&b, line, row); //
    technically, it's useless to store it since we know it's the player's one,
    but anyways board_push(&b, line - 1, row, hedgehog);
                }
            }
            else if(direction == 'B') {
                if(line == GRIDHEIGHT) printf("Vous ne pouvez pas vous
    déplacer vers le bas.\n"); else { char hedgehog = board_pop(&b, line,
    row); // technically, it's useless to store it since we know it's the
    player's one, but anyways board_push(&b, line + 1, row, hedgehog);
                }
            }

            board_print(&b, rolled_line + 1);
        }
    }*/
        board_print(&b, rolled_line + 1);
      }

      if (board_is_line_empty(&b, rolled_line, GRIDWIDTH)) {
        printf("Line %d has no more movable hedgehog; no more actions needed\n",
               rolled_line + 1);
      } else {

        int col = input_column() - 'A';

        printf("DEBUG : player picked col %d\n", col);

        bool move_ok = false;

        while (!move_ok) {
          bool passed = true;
          if (col < 0 || col >= GRIDWIDTH) {
            printf("This column is out of range\n");
            passed = false;
          } else if (board_height(&b, rolled_line, col) < 1) {
            printf("This tile is empty\n");
            passed = false;
          } else if (col == GRIDWIDTH - 1) {
            printf("This hedgehog cannot move\n");
            passed = false;
          } else if (board_check_trapped(&b, rolled_line, col) &&
                     !board_is_line_empty(&b, rolled_line, col)) {
            printf("This hedgehog is trapped.");
            passed = false;
          }
          if (passed) {
            move_ok = true;
          } else {
            char col = input_column();
            col -= 'A';
          }
        }

        /*if(board_height(&b, rolled_line, row) == 0) printf("Cette case est
        vide !\n"); else if(row == GRIDWIDTH - 1) printf("Ce hérisson ne
        peut plus avancer !\n"); else if(board_check_trapped(&b,
        rolled_line, row) && !board_is_line_empty(&b, rolled_line, row)) {
            printf("Impossible de déplacer le hérisson : il est piégé et il
        reste d'autres hérissons avant lui.");
        }*/

        char hedgehog = board_pop(&b, rolled_line, col);
        int hedgehog_team = hedgehog - 'A';
        board_push(&b, rolled_line, col + 1, hedgehog);

        // one hedgehog crossed the finish line !
        if (col + 1 == GRIDWIDTH - 1) {
          board_add_won_hedgehog(&b, hedgehog_team);
          // using >= so that it ends the game even if there's only one
          // hedgehog per player
          if (board_get_won_hedgehogs(&b, hedgehog_team) >=
              HEDGEHOGSPERPLAYER - 1) {
            game_over = true;
          }
        }
      }
    }
  }

  // the game is over, apparently
  printf("=== GAME OVER ===\n");
  int place = 1;
  for (int hedgehog_count = HEDGEHOGSPERPLAYER; hedgehog_count >= 0;
       hedgehog_count--) {
    printf("Place #%d : ",place);
    for (int player = 0; player < PLAYERCOUNT; player++) {
      if (board_get_won_hedgehogs(&b, player) == hedgehog_count) {
        printf("équipe %c,", player + 'A');
        place++;
      }
    }
    printf(" avec %d hérissons\n", hedgehog_count);

    if (place == PLAYERCOUNT)
      break;
  }
  return 0;
}
