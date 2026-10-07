#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
// #include "board.h"

const int player_count = 4;

int de() {
    return rand() % 6 + 1;
}

// TODO : move input logic to dedicated functions in order to avoid some obvious bugs

int main(void) {
    srand(time(NULL));

    int trapped_tiles[GRID_HEIGHT][GRID_WIDTH] = {
        { 0, 1, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    }
    board_t* b = board_make(trapped_tiles);

    bool game_over = false;
    while(!game_over) {
        for(int player = 0 ; player < player_count ; player++) {
            int player_name = player + 65; // 65 is the ascii code for 'A'
            printf("Au tour du joueur %d ! \n", player + 1);

            int rolled_value = de();

            printf("On lance le dé... vous avez obtenu un %d !\n", rolled_value);

            printf("Souhaitez-vous déplacer un hérisson ? (O/N) ");

            char move_hedgehog;
            scanf(" %c", &move_hedgehog);

            if(move_hedgehog == 'O') {
                printf("Indiquez le hérisson à déplacer : ");

                char row = 'z';
                int line = 42;
                scanf(" %c%i", &row, &line);
                row -= 97;
                line--;

                // printf("On a sélectionné la row %d et la line %d \n", row, line);

                char player_owning_cell = board_top(b, line, row);

                if(player_owning_cell != player_name) printf("Ce hérisson n'appartient pas à votre équipe.\n");
                else {
                    printf("Indiquez la direction du déplacement (T/B): ");
                    char direction = 'N';
                    scanf(" %c", &direction);

                    if(direction == 'T')
                }
            }





        }
    }

}
