#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"

const int player_count = 4;

int de() {
    return rand() % 6 + 1;
}

// TODO : move input logic to dedicated functions in order to avoid some obvious bugs

int main(void) {
    srand(time(NULL));

    int trapped_tiles[GRIDHEIGHT][GRIDWIDTH] = {
        { 0, 1, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    board_t b;
    board_init(&b, trapped_tiles);

    bool game_over = false;
    while(!game_over) {
        for(int player = 0 ; player < player_count ; player++) {
            int player_name = player + 65; // 65 is the ascii code for 'A'
            printf("Au tour du joueur %d ! \n", player + 1);

            board_print(&b, -1);

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

                char player_owning_cell = board_top(&b, line, row);

                if(player_owning_cell != player_name) printf("Ce hérisson n'appartient pas à votre équipe.\n");
                else {
                    printf("Indiquez la direction du déplacement (H/B): ");
                    char direction = 'N';
                    scanf(" %c", &direction);

                    if(direction == 'T') {
                        if(line == 0) printf("Vous ne pouvez pas vous déplacer vers le haut.\n");
                        else if(line == GRIDHEIGHT) printf("Vous ne pouvez pas vous déplacer vers le bas.\n");
                        else {
                            char hedgehog = board_pop(&b, line, row); // technically, it's useless to store it since we know it's the player's one, but anyways
                            board_push(&b, line, row, hedgehog);
                        }
                    }
                }
            }





        }
    }

}
