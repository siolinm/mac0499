CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = heap.o util.o cert.o main.o menu.o currentTime.o pq.o

heap: $(O)
	gcc $(CFLAGS) $(O) -o heap 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o heap
