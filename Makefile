output: main.o
	g++ main.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o
