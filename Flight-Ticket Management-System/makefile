all: flightticket.o flighthashtable.o main.o mylist.o
	g++ -o main main.o flightticket.o flighthashtable.o mylist.o

main.o:
	g++ -c main.cpp

flightticket.o:
	g++ -c flightticket.cpp
	
flighthashtable.o:
	g++ -c flighthashtable.cpp

mylist.o:
	g++ -c mylist.cpp


clean:
	rm -f main main.o flightticket.o flighthashtable.o mylist.o