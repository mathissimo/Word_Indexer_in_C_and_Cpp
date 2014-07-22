OBJECTS=Liste.o Wortindex.o Dateien.o
CC=cc  #change compiler here
OPTIONS=-std=c99 -Wall -g

lt : ListTest.c $(OBJECTS)
	$(CC) $(OPTIONS) -o lt ListTest.c $(OBJECTS)
Liste.o : Liste.c Liste.h
	$(CC) $(OPTIONS) -c Liste.c
Wortindex.o : Wortindex.c Wortindex.h Liste.h
	$(CC) $(OPTIONS) -c Wortindex.c
Dateien.o : Dateien.c Dateien.h
	$(CC) $(OPTIONS) -c Dateien.c
memtest : lt
	rm pdd
	valgrind --leak-check=full --show-reachable=yes ./lt -w=2 pdd Youth.txt Monolog.txt
clean:
	rm lt $(OBJECTS)
