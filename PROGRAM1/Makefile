main.exe: main.o WordLadder.o
	g++ -Wall -Werror main.o WordLadder.o -o main.exe 
	./main.exe < test.txt
	./main.exe < test.1.txt
	./main.exe < test.2.txt
	
main.o: main.cpp WordLadder.cpp WordLadder.h
	g++ -Wall -Werror -c main.cpp WordLadder.cpp
	
WordLadder.o: WordLadder.cpp WordLadder.h
	g++ -Wall -Werror -c WordLadder.cpp

clean:
	rm *.o *.exe output.txt