#include "board.h"
#include "input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// const int player_count = 4;

int roll_dice() { return rand() % 6 + 1; }

int main(int argc, char* argv[]) {
  // let's define some variables for extensions
  // since we only implement 2 simple extensions, there is no need to put this in another struct / file yet
  // EXTENSION 1 : doping
  bool ext_hedgehog_on_drugs = false;
  bool ext_doped_hedgehog_finished = false;

  // EXTENSION 2 : sandwiches
  bool ext_sandwiches = false;

  // let's see if the user enabled some extensions...
  if(argc == 2) {
    printf("Enabling extensions...\n");
    // let's see the codes of enabled extensions
    for(int i = 0 ; argv[1][i] != '\0' ; i++) {
      switch(argv[1][i]) {
        case 'd':
          if(!ext_hedgehog_on_drugs) printf("<Doping hedgehog> enabled\n");
          ext_hedgehog_on_drugs = true;
          break;
        case 's':
          if(!ext_sandwiches) printf("<Sandwiches> enabled\n");
          ext_sandwiches = true;
          break;
        default:
          printf("WARNING : unrecognized extension code %c\n", argv[1][i]);
          break;
      }
    }
  }

  srand(time(NULL));

  int trapped_tiles[GRIDHEIGHT][GRIDWIDTH] = {{0, 0, 1}, {0, 0, 0}, {0, 0, 0}};

  board_t b;

  board_init(&b, trapped_tiles);

  // placing hedgehogs, because the game is a bit boring when there aren't any
  // hedgehogs yet
  for(int player = 0 ; player < PLAYERCOUNT ; player++) {
    for (int i = 0; i < HEDGEHOGSPERPLAYER; i++) {
        board_push(&b, roll_dice() % GRIDHEIGHT, 0, player + 'A');
    }
  }

  bool game_over = false;

  while (!game_over) {
    for (int player = 0; player < PLAYERCOUNT; player++) {
      int player_name = player + 'A';
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
        move_hedgehog = input_YN();
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
        board_print(&b, rolled_line + 1);
      }

      if (board_is_line_empty(&b, rolled_line, GRIDWIDTH)) {
        printf("Line %d has no more movable hedgehog; no more actions needed\n",
               rolled_line + 1);
      } else {

        int col = input_column() - 'A';


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
            col = input_column() - 'A';
          }
        }

        char hedgehog = board_pop(&b, rolled_line, col);
        int hedgehog_team = hedgehog - 'A';
        board_push(&b, rolled_line, col + 1, hedgehog);

        if (col + 1 == GRIDWIDTH - 1) {
          // one hedgehog crossed the finish line ! however, we don't care if it's the doped one...
          if(ext_hedgehog_on_drugs && !ext_doped_hedgehog_finished) {
            printf("This hedgehog crossed the finish line ! However, its performance was so good it was accused of doping. Too bad !\n");
            ext_doped_hedgehog_finished = true;
          }
          else {
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
  }

  // the game is over, apparently
  printf("=== GAME OVER ===\n");
  int place = 1;
  // let's print the leaderboard
  for (int hedgehog_count = HEDGEHOGSPERPLAYER; hedgehog_count >= 0 && place <= PLAYERCOUNT;
       hedgehog_count--) {
    // let's find out if a team actually won with that many hedgehogs
    bool valid_count = false;
    for(int player = 0 ; player < PLAYERCOUNT ; player++) {
        if(board_get_won_hedgehogs(&b, player) == hedgehog_count) valid_count = true;
    }

    // we should only print this line of the leaderboard if at least someone won with that many hedgehogs
    if(valid_count) {
        printf("Place #%d : ", place);
        for (int player = 0; player < PLAYERCOUNT; player++) {
          if (board_get_won_hedgehogs(&b, player) == hedgehog_count) {
            printf("équipe %c, ", player + 'A');
            place++;
          }
        }
        printf("avec %d hérissons\n", hedgehog_count);
    }
  }

  return 0;
}
