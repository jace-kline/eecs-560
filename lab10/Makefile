prog: main.o DSHandler.o DSetCollection.o DNode.o IO.o
	g++ -std=c++11 -g -Wall IO.o DNode.o DSetCollection.o DSHandler.o main.o -o prog

main.o: main.cpp DSHandler.h IO.h
	g++ -std=c++11 -g -Wall -c  main.cpp

DSHandler.o : DSHandler.h DSHandler.cpp DisjointSet/DSetCollection.h IO.h
	g++ -std=c++11 -g -Wall -c  DSHandler.cpp

DSetCollection.o: DisjointSet/DSetCollection.h DisjointSet/DSetCollection.cpp DisjointSet/DNode.h
	g++ -std=c++11 -g -Wall -c  DisjointSet/DSetCollection.cpp

DNode.o: DisjointSet/DNode.h DisjointSet/DNode.cpp
	g++ -std=c++11 -g -Wall -c  DisjointSet/DNode.cpp

IO.o: IO.h IO.cpp
	g++ -std=c++11 -g -Wall -c  IO.cpp

clean:
	rm prog *.o