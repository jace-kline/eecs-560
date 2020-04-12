prog: main.o Maxmin.o IO.o Game.o 
	g++ -std=c++11 -g -Wall Game.o IO.o Maxmin.o main.o -o prog

main.o: main.cpp Maxmin.h IO.h
	g++ -std=c++11 -g -Wall -c  main.cpp

Maxmin.o: Maxmin.h Maxmin.cpp Game.h
	g++ -std=c++11 -g -Wall -c  Maxmin.cpp

IO.o: IO.h IO.cpp Game.h 
	g++ -std=c++11 -g -Wall -c  IO.cpp

Game.o: Game.h Game.cpp
	g++ -std=c++11 -g -Wall -c  Game.cpp

clean:
	rm prog *.o