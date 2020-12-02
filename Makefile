output: main.o menu.o
	g++ main.o menu.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

menu.o: menu.cpp menu.h
	g++ -std=c++11 -c menu.cpp

clean:
	rm *.o
