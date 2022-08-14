CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = util.o cert.o main.o menu.o currentTime.o avl.o queries.o pq.o

bst: $(O)
	gcc $(CFLAGS) $(O) -o bst 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o bst