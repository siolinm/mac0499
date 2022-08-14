CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = tourn.o util.o cert.o main.o menu.o currentTime.o pq.o avl.o

tourn: $(O)
	gcc $(CFLAGS) $(O) -o tourn 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o tourn
