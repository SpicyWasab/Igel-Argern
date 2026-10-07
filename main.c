#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"

// const int player_count = 4;

int roll_dice() {
    return rand() % 6 + 1;
}

bool board_is_line_empty(board_t *b, int line, int max_row) {
    for(int i = 0 ; i < max_row ; i++) {
        if(board_height(b, line, i) != 0) return false;
    }

    return true;
}

bool board_check_trapped(board_t *b, int line, int row) {
    return b->tiles[GRIDWIDTH * line + row].trapped;
}

// TODO : move input logic to dedicated functions in order to avoid some obvious bugs

int main(void) {
    srand(time(NULL));

    int trapped_tiles[GRIDHEIGHT][GRIDWIDTH] = {
        { 0, 0, 1 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    board_t b;
    printf("hey !\n");
    board_init(&b, trapped_tiles);
    printf("hey !\n");

    // placing hedgehogs, because the game is a bit boring when there aren't any hedgehogs yet
    for(int i = 0 ; i < HEDGEHOGS ; i++) {
        board_push(&b, roll_dice() % GRIDHEIGHT, 0, i % PLAYERCOUNT + 'A');
    }
    printf("hey !\n");


    for(int i = 0 ; i < GRIDHEIGHT ; i++) {
        for(int j = 0 ; j < GRIDWIDTH ; j++) {
            printf("(%d, %d) vaut %d\n", i, j, (int)b.tiles[GRIDWIDTH * i + j].trapped);
        }
    }

    bool game_over = false;
    while(!game_over) {
        for(int player = 0 ; player < PLAYERCOUNT ; player++) {
            int player_name = player + 65; // 65 is the ascii code for 'A'
            printf("Au tour du joueur %d ! \n", player_name);

            board_print(&b, -1);

            int rolled_line = roll_dice();

            printf("On lance le dé... vous avez obtenu un %d !\n", rolled_line);

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
                        else {
                            char hedgehog = board_pop(&b, line, row); // technically, it's useless to store it since we know it's the player's one, but anyways
                            board_push(&b, line - 1, row, hedgehog);
                        }
                    }
                    else if(direction == 'B') {
                        if(line == GRIDHEIGHT) printf("Vous ne pouvez pas vous déplacer vers le bas.\n");
                        else {
                            char hedgehog = board_pop(&b, line, row); // technically, it's useless to store it since we know it's the player's one, but anyways
                            board_push(&b, line + 1, row, hedgehog);
                        }
                    }
                }
            }

            if(board_is_line_empty(&b, rolled_line, GRIDWIDTH - 1)) printf("La ligne %d n'a aucun hérisson déplaçable ; pas d'autre action à réaliser. \n", rolled_line);
            else {
                printf("Indiquez la colonne du hérisson à déplacer sur la ligne %d : ", rolled_line);

                char row = 'z';
                scanf(" %c", &row);
                row -= 97;

                if(board_height(&b, rolled_line, row) == 0) printf("Cette case est vide !\n");
                else if(row == GRIDWIDTH - 1) printf("Ce hérisson ne peut plus avancer !\n");
                else if(board_check_trapped(&b, rolled_line, row) && !board_is_line_empty(&b, rolled_line, row)) {
                    printf("Impossible de déplacer le hérisson : il est piégé et il reste d'autres hérissons avant lui.");
                }

                char hedgehog = board_pop(&b, rolled_line, row);
                board_push(&b, rolled_line, row + 1, hedgehog);
            }






        }
    }

}
