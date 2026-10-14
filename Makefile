CFLAGS = -Wall -Wextra

dev:
	gcc $(CFLAGS) -g -o igel-argern ./main.c ./board.c ./input.c

prod:
	gcc $(CFLAGS) -o igel-argern ./main.c ./board.c ./input.c

clean:
	rm ./igel-argern
