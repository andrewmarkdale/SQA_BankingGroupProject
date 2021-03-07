main: main.o Transaction.o Session.o
	g++ -std=c++11 main.o Transaction.o Session.o -o main

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Transaction.o: Transaction.cpp
	g++ -std=c++11 -c Transaction.cpp

Session.o: Session.cpp
	g++ -std=c++11 -c Session.cpp

clean:
	rm *.o main
