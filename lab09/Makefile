prog: main.o IO.o Test.o Heap.o Node.o
	g++ -std=c++11 -g -Wall Node.o Heap.o Test.o IO.o main.o -o prog

main.o: main.cpp Test.h IO.h
	g++ -std=c++11 -g -Wall -c  main.cpp

Test.o: Test.h Test.cpp Heap.h
	g++ -std=c++11 -g -Wall -c  Test.cpp

IO.o: IO.h IO.cpp
	g++ -std=c++11 -g -Wall -c  IO.cpp

Heap.o: Heap.h Heap.cpp Node.h
	g++ -std=c++11 -g -Wall -c  Heap.cpp

Node.o: Node.h Node.cpp
	g++ -std=c++11 -g -Wall -c  Node.cpp

clean:
	rm prog *.o