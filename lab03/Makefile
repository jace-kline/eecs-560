prog: main.o TableHandler.o HashTable.o Bucket.o User.o
	g++ -std=c++11 -g -Wall User.o Bucket.o HashTable.o TableHandler.o main.o -o prog

main.o: main.cpp TableHandler.h
	g++ -std=c++11 -g -Wall -c  main.cpp

TableHandler.o: TableHandler.h TableHandler.cpp HashTable.h User.h
	g++ -std=c++11 -g -Wall -c  TableHandler.cpp

HashTable.o: HashTable.h HashTable.cpp Bucket.h User.h
	g++ -std=c++11 -g -Wall -c  HashTable.cpp

Bucket.o: Bucket.h Bucket.cpp User.h
	g++ -std=c++11 -g -Wall -c  Bucket.cpp

User.o: User.h User.cpp
	g++ -std=c++11 -g -Wall -c  User.cpp

clean:
	rm prog *.o