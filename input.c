/*Move_or_not asks if the player wants to move a hegehog
Move gives the move that a player wanted (column,line,direction)
column gives the column where to move the second hedgehog*/

#include <stdbool.h>
#include <stdio.h>

void flush_stdin() {
  while (getchar() != '\n')
    ;
}

// reads from stdin and returns false if there's an issue, true otherwise
bool safe_input(char *str, int size) {
  if (fgets(str, size, stdin) != NULL) { // if there's no issue
    for (int i = 0; i < size; i++) {     // try to find newline
      if (str[i] == '\n')
        return true; // we found a newline, that's great, let's stop !
    }

    // if we get there, the input string was too long and didn't fit in str, so
    // let's flush and return false
    flush_stdin();
    return false;
  } else { // if fgets failed
    flush_stdin();
    return false;
  }
}

// ask the user if he wants to move a hedgehog
bool input_YN() {
  char move_hedgehog[3]; // size 3 to account for both \n and \0
  while (true) {
    bool input_successful = safe_input(move_hedgehog, 3);

    if (input_successful) {
      switch (move_hedgehog[0]) {
      case 'Y':
        return true;
      case 'y':
        return true;
      case 'N':
        return false;
      case 'n':
        return false;
      }
    }

    // if we didn't return anything, the input wasn't successful or didn't match
    // our expectations
    printf("Please answer again (Y/n) ");
  }
}

// asks the user for a valid move and writes it
void input_move(char result[3]) {
  // Format RowLineDirection (CAPS) - example : A1T, D3B
  printf("What is your move? Ex : A1B, B3T... (Square+Top/Bottom)");

  char move[5]; // this will hold the input

  while (true) {
    bool input_successful = safe_input(move, 5);

    if (input_successful) {
      if (move[0] >= 'A' &&
          move[0] <= 'Z') { // if first char is in the alphabet
        if (move[1] >= '0' && move[1] <= '9') { // if second char is a digit
          if (move[2] == 'T' || move[2] == 't' || move[2] == 'B' ||
              move[2] == 'b') { // if third char is a move
            // let's copy the input and interrupt the function
            result[0] = move[0];
            result[1] = move[1];
            result[2] = move[2];
            return;
          }
        }
      }
    }

    printf("Please try again.");
  }
}

char input_column() {
  // Format ROW (CAPS) - example : A,B,C...
  printf("What is your move? Format: ROW (A,B,C ...)");

  char move[3];
  while (true) {
    bool input_successful = safe_input(move, 3);
    if (input_successful) {
      if (move[0] >= 'A' && move[0] <= 'Z') {
        return move[0];
      }
    }

    // something went wrong !
    printf("Please try again. ");
  }
}
