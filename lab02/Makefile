prog: main.o HashTable.o List.o Node.o
	g++ -std=c++11 -g -Wall Node.o List.o HashTable.o main.o -o prog

main.o: main.cpp Player.h HashTable.h
	g++ -std=c++11 -g -Wall -c  main.cpp

HashTable.o: HashTable.h HashTable.cpp HashTableInterface.h List.h
	g++ -std=c++11 -g -Wall -c  HashTable.cpp

List.o: List.h List.cpp ListInterface.h Node.h
	g++ -std=c++11 -g -Wall -c  List.cpp

Node.o: Node.h Node.cpp
	g++ -std=c++11 -g -Wall -c  Node.cpp

clean:
	rm prog *.o