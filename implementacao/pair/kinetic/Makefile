CFLAGS = -Wall -g3 -pedantic -Wno-unused-result # g3 remove qualquer otimização, remover essa flag depois
OBJS   = event.o menu.o orderedlist.o pq.o tourn.o util.o maxima.o heapsort.o kds.o splay_tree.o draw.o
LIBS   = -lm -lX11 -lcairo

kineticpair: $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o kineticpair $(LIBS)

%.o: %.c %.h debug.h util.h draw.h
	gcc $(CFLAGS) -c $<

random_points:
	gcc $(CFLAGS) random_points.c -o random_points -lm

clean:
	rm *.o kineticpair random_points *~