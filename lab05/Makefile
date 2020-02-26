prog: main.o Tester.o IntHash.o HashTable.o Bucket.o
	g++ -std=c++11 -g -Wall IntHash.o Bucket.o HashTable.o Tester.o main.o -o prog

main.o: main.cpp Tester.h
	g++ -std=c++11 -g -Wall -c  main.cpp

Tester.o: Tester.h Tester.cpp HashTable.h IntHash.h
	g++ -std=c++11 -g -Wall -c  Tester.cpp

IntHash.o: IntHash.h IntHash.cpp
	g++ -std=c++11 -g -Wall -c  IntHash.cpp

HashTable.o: HashTable.h HashTable.cpp Bucket.h
	g++ -std=c++11 -g -Wall -c  HashTable.cpp

Bucket.o: Bucket.h Bucket.cpp
	g++ -std=c++11 -g -Wall -c  Bucket.cpp

clean:
	rm prog *.o