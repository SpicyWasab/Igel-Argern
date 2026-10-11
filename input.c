/*Move_or_not asks if the player wants to move a hegehog
Move gives the move that a player wanted (column,line,direction)
column gives the column where to move the second hedgehog*/

#include <stdbool.h>
#include <stdio.h>

bool move_or_not() {
  printf("Would you like to move a hedgehog? (Y/n) ");

  char move_hedgehog[2];
  while (true) {
    fgets(move_hedgehog, 2, stdin);
    if (move_hedgehog != NULL) {
      switch (move_hedgehog[0]) {
      case 'Y':
        return true;
      case 'y':
        return true;
      case 'N':
        return false;
      case 'n':
        return false;
      default:
        printf("Please answer again (Y/n)");
      }
    }
  }
}

char *move() {
  // Format RowLineDirection (CAPS) - example : A1T, D3B
  printf("What is your move? Format: ROWlineDIRECTION (Direction: T top, B "
         "bottom) (A1B, B2T...)");

  char move[4];

  while (true) {
    fgets(move, 4, stdin);
    if (move != NULL) {
      if (move[0] < 65 || move[0] > 90) {
        if (move[1] > 30 && move[1] < 40) {
          if (move[2] == 'T' || move[2] == 't' || move[2] == 'B' ||
              move[2] == 'b') {
            return move;
          }
        }
      }
    }
    printf("Try again ( Format: ROWlineDIRECTION (Direction: T top, B bottom) "
           "(A1B, B2T...) )");
    fgets(move, 4, stdin);
  }
}

char *column() {
  // Format ROW (CAPS) - example : A,B,C...
  printf("What is your move? Format: ROW (A,B,C ...)");

  char move[2];

  while (true) {
    fgets(move, 2, stdin);
    if (move != NULL) {
      if (move[0] < 65 || move[0] > 90) {
        return move;
      }
    }
    printf("Try again ( Format: ROW (A,B,C ...) )");
    fgets(move, 2, stdin);
  }
  return move;
}
