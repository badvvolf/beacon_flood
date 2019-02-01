all : beacon_flood

beacon_flood: main.o
	g++ -o beacon_flood main.o -ltins
main.o: main.cpp
	g++ -g -c -o main.o main.cpp
clear:
	rm -f *.o
	rm -f beacon_flood
