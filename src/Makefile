CC=gcc
FLAGS= -std=c99 -W -Wall -g

FC:FC.o CSP.h CSP_reader.o utils.o
	$(CC) $^ -o $@

FC_heuristique:FCh.o CSP.h CSP_reader.o utils.o
	$(CC) $^ -o $@
%.o: %.c
	$(CC) $(FLAGS) -c  $^

clean::
	rm *.o
