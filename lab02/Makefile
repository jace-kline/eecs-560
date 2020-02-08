prog: main.o HashTable.o List.o Node.o Player.o
	g++ -std=c++11 -g -Wall Player.o Node.o List.o HashTable.o main.o -o prog

main.o: main.cpp Player.h HashTable.h
	g++ -std=c++11 -g -Wall -c  main.cpp

HashTable.o: HashTable.h HashTable.cpp List.h Player.h
	g++ -std=c++11 -g -Wall -c  HashTable.cpp

List.o: List.h List.cpp Node.h Player.h
	g++ -std=c++11 -g -Wall -c  List.cpp

Node.o: Node.h Node.cpp Player.h
	g++ -std=c++11 -g -Wall -c  Node.cpp

Player.o: Player.h Player.cpp
	g++ -std=c++11 -g -Wall -c  Player.cpp

clean:
	rm prog *.o