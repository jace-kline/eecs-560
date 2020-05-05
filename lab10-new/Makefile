prog: main.o DSHandler.o GraphHandler.o WGraph.o DSetCollection.o DNode.o Heap.o List.o Node.o WEdge.o AdjEntry.o IO.o
	g++ -std=c++11 -g -Wall IO.o AdjEntry.o WEdge.o Heap.o Node.o List.o DNode.o DSetCollection.o WGraph.o GraphHandler.o DSHandler.o main.o -o prog

main.o: main.cpp DSHandler.h GraphHandler.h IO.h
	g++ -std=c++11 -g -Wall -c  main.cpp

DSHandler.o : DSHandler.h DSHandler.cpp DisjointSet/DSetCollection.h IO.h
	g++ -std=c++11 -g -Wall -c  DSHandler.cpp

GraphHandler.o: GraphHandler.h GraphHandler.cpp Graph/WGraph.h
	g++ -std=c++11 -g -Wall -c  GraphHandler.cpp

WGraph.o: Graph/WGraph.h Graph/WGraph.cpp DisjointSet/DSetCollection.h Heap/Heap.h List/List.h
	g++ -std=c++11 -g -Wall -c  Graph/WGraph.cpp

DSetCollection.o: DisjointSet/DSetCollection.h DisjointSet/DSetCollection.cpp DisjointSet/DNode.h
	g++ -std=c++11 -g -Wall -c  DisjointSet/DSetCollection.cpp

DNode.o: DisjointSet/DNode.h DisjointSet/DNode.cpp
	g++ -std=c++11 -g -Wall -c  DisjointSet/DNode.cpp

List.o: List/List.h List/List.cpp List/Node.h
	g++ -std=c++11 -g -Wall -c  List/List.cpp

Node.o: List/Node.h List/Node.cpp Graph/WEdge.h Graph/AdjEntry.h
	g++ -std=c++11 -g -Wall -c  List/Node.cpp

Heap.o: Heap/Heap.h Heap/Heap.cpp Graph/WEdge.h
	g++ -std=c++11 -g -Wall -c  Heap/Heap.cpp

WEdge.o: Graph/WEdge.h Graph/WEdge.cpp
	g++ -std=c++11 -g -Wall -c  Graph/WEdge.cpp

AdjEntry.o: Graph/AdjEntry.h Graph/AdjEntry.cpp
	g++ -std=c++11 -g -Wall -c  Graph/AdjEntry.cpp

IO.o: IO.h IO.cpp
	g++ -std=c++11 -g -Wall -c  IO.cpp

clean:
	rm prog *.o