main.exe: main.o BSTree.o Node.o testharness
	g++ -Wall -Werror main.o BSTree.o Node.o -o main.exe 
	./main.exe
	
main.o: main.cpp BSTree.cpp BSTree.h Node.cpp Node.h
	g++ -Wall -Werror -c main.cpp BSTree.cpp Node.cpp
	
BSTree.o: BSTree.cpp BSTree.h Node.cpp Node.h
	g++ -Wall -Werror -c WordLadder.cpp

Node.o: Node.cpp Node.h
	g++ -Wall -Werror -c Node.cpp

clean:
	rm *.o *.exe