all : clean main

main : main.c
	gcc -o $@ $^ -std=c99 -Wall -O2 -lm

clean :
	rm -f main
