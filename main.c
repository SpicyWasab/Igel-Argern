#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int player_count = 4;

int de() {
    return rand() % 6 + 1;
}

int main(void) {
    srand(time(NULL));

    // board_t* b = let's figure this out later

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
                printf("Entrez le hérisson à déplacer : \n");
    
                char column = 'z';
                int row = 42;
                scanf(" %c%i", &column, &row);
                column -= 97;
                row--;

                printf("On a sélectionné la colonne %d et la ligne %d \n", column, row);

                // char player_owning_cell = board_peek(b)
            }



        }
    }

}
