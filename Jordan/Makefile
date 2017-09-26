jordan.o: jordan.cpp jordan.h
	g++ -c jordan.cpp -o jordan.o
main.o: main.cpp jordan.h
	g++ -c main.cpp -o main.o
main: main.o jordan.o
	g++ main.o jordan.o -o main
clear:
	rm  *.o
