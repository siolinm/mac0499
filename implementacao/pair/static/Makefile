CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = splay.o menu.o util.o heapsort.o main.o

pair: $(O)
	gcc $(CFLAGS) $(O) -o pair -lm

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o pair points brute *~

brute: brute.c
	gcc -o brute brute.c -lm

points: generate.c
	gcc -o points generate.c
