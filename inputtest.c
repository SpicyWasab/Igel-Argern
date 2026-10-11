#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input.h"

int main(void) {
    bool decision1 = input_move_or_not();
    bool decision2 = input_move_or_not();
    bool decision3 = input_move_or_not();

    printf("D1 : %d, D2 : %d, D3 : %d\n", decision1, decision2, decision3);

    char m1[5];
    char m2[5];
    char m3[5];

    input_move(m1);
    input_move(m2);
    input_move(m3);

    printf("%c, %c, %c\n", input_column(), input_column(), input_column());

    return 0;
}
