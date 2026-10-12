#ifndef INPUT_H
#define INPUT_H

void flush_stdin();

bool safe_input(char* str, int size);

bool input_move_or_not();

void input_move(char result[3]);

char input_column();

#endif
