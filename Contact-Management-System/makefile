all: contact.o contactbst.o main.o myvector.o
	g++ -o main main.o contact.o contactbst.o myvector.o

main.o:
	g++ -c main.cpp

contact.o:
	g++ -c contact.cpp
	
contactbst.o:
	g++ -c contactbst.cpp

myvector.o:
	g++ -c myvector.cpp


clean:
	rm -f main main.o contact.o contactbst.o myvector.o