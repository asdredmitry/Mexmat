jordan.o: jordan.cpp jordan.h
	g++ -c -W jordan.cpp -o jordan.o
main.o: main.cpp jordan.h
	g++ -c -W main.cpp -o main.o
main: main.o jordan.o
	g++ -W main.o jordan.o -o main
clear:
	rm  *.o
