OBJECTS=IndexerApp.o Liste.o WortIndex.o ListenElement.o
CC=cpp   #Change compiler here ***
OPTIONS=-Wall -g

iapp : start.cpp $(OBJECTS)
	$(CC) $(OPTIONS) -o iapp start.cpp $(OBJECTS)
IndexerApp.o : IndexerApp.cpp
	$(CC) $(OPTIONS) -c IndexerApp.cpp
Liste.o : Liste.cpp Liste.hpp ListenElement.hpp
	$(CC) $(OPTIONS) -c Liste.cpp
WortIndex.o : WortIndex.cpp WortIndex.hpp Liste.hpp
	$(CC) $(OPTIONS) -c WortIndex.cpp
ListenElement.o : ListenElement.cpp ListenElement.hpp
	$(CC) $(OPTIONS) -c ListenElement.cpp
memtest : iapp
	rm pdd
	valgrind --leak-check=full ./iapp -w=2 pdd Test.txt
clean:
	rm iapp $(OBJECTS)
