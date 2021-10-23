all : clean cconv

cconv : cconv.c
	gcc -o $@ $^ -std=c99 -Wall -lm

clean :
	rm -f cconv
