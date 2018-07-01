# Makefile for virtuoso-solver

CFLAGS = -std=gnu++11 -O2 -Wall

temp: virtuoso.cpp
	g++ -o a virtuoso.cpp $(CFLAGS)

main: main.cpp virtuoso_solver.o
	g++ -o main main.cpp virtuoso_solver.o $(CFLAGS)

virtuoso_solver.o: virtuoso_solver.h virtuoso_solver.cpp
	g++ -c virtuoso_solver.cpp $(CFLAGS)

clean:
	rm -rf *.o *.exe* main
