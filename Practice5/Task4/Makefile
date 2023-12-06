CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: main Child

main_program: main.c
	$(CC) $(CFLAGS) $< -o $@

child_program: Child.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f main Child

