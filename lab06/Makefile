prog: main.o Manager.o BinaryTree.o Node.o
	g++ -std=c++11 -g -Wall Node.o BinaryTree.o Manager.o main.o -o prog

main.o: main.cpp Manager.h
	g++ -std=c++11 -g -Wall -c  main.cpp

Manager.o: Manager.h Manager.cpp BinaryTree.h
	g++ -std=c++11 -g -Wall -c  Manager.cpp

BinaryTree.o: BinaryTree.h BinaryTree.cpp Node.h
	g++ -std=c++11 -g -Wall -c  BinaryTree.cpp

Node.o: Node.h Node.cpp
	g++ -std=c++11 -g -Wall -c  Node.cpp

clean:
	rm prog *.o