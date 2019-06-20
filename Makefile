Project1: transform generate solve

transform: transform.o 
	g++ -o transform transform.o

generate: generate.o
	g++ -o generate generate.o

solve: solve.cpp
	g++ -O3 -o solve solve.cpp

transform.o: transform.cpp sudoku.h
	g++ -c transform.cpp

generate.o: generate.cpp sudoku.h
	g++ -c generate.cpp

clean:
	rm transform generate solve *.o
