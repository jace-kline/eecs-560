prog: main.o TreeHandler.o BinaryTree.o Node.o Movie.o
	g++ -std=c++11 -g -Wall Movie.o Node.o BinaryTree.o TreeHandler.o main.o -o prog

main.o: main.cpp TreeHandler.h
	g++ -std=c++11 -g -Wall -c  main.cpp

TreeHandler.o: TreeHandler.h TreeHandler.cpp BinaryTree.h Movie.h
	g++ -std=c++11 -g -Wall -c  TreeHandler.cpp

BinaryTree.o: BinaryTree.h BinaryTree.cpp Node.h Movie.h
	g++ -std=c++11 -g -Wall -c  BinaryTree.cpp

Node.o: Node.h Node.cpp Movie.h
	g++ -std=c++11 -g -Wall -c  Node.cpp

Movie.o: Movie.h Movie.cpp
	g++ -std=c++11 -g -Wall -c  Movie.cpp

clean:
	rm prog *.o