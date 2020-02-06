prog: main.o List.o Node.o
	g++ -std=c++11 -g -Wall Node.o List.o main.o -o prog

main.o: main.cpp List.h
	g++ -std=c++11 -g -Wall -c  main.cpp

List.o: List.h List.cpp ListInterface.h Node.h
	g++ -std=c++11 -g -Wall -c  List.cpp

Node.o: Node.h Node.cpp
	g++ -std=c++11 -g -Wall -c  Node.cpp

clean:
	rm prog *.o
