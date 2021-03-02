main: main.o Transaction.o Session.o
	g++ main.o Transaction.o Session.o -o main

main.o: main.cpp
	g++ -c main.cpp

Transaction.o: Transaction.cpp
	g++ -c Transaction.cpp

Session.o: Session.cpp
	g++ -c Session.cpp

clean:
	rm *.o main
