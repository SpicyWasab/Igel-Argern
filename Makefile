CFLAGS = -Wall -Wextra -Werror

dev:
	gcc $(CFLAGS) -g -o igel-argern ./main.c

prod:
	gcc $(CFLAGS) -o igel-argern ./main.c

clean:
	rm ./igel-argern