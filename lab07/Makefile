prog: main.o DoctorManager.o PatientManager.o Heap.o IO.o Record.o 
	g++ -std=c++11 -g -Wall Record.o IO.o Heap.o PatientManager.o DoctorManager.o main.o -o prog

main.o: main.cpp DoctorManager.h PatientManager.h
	g++ -std=c++11 -g -Wall -c  main.cpp

DoctorManager.o: DoctorManager.h DoctorManager.cpp Heap.h IO.h
	g++ -std=c++11 -g -Wall -c  DoctorManager.cpp

PatientManager.o: PatientManager.h PatientManager.cpp Heap.h IO.h
	g++ -std=c++11 -g -Wall -c  PatientManager.cpp

Heap.o: Heap.h Heap.cpp Record.h
	g++ -std=c++11 -g -Wall -c  Heap.cpp

IO.o: IO.h IO.cpp Record.h 
	g++ -std=c++11 -g -Wall -c  IO.cpp

Record.o: Record.h Record.cpp
	g++ -std=c++11 -g -Wall -c  Record.cpp

clean:
	rm prog *.o