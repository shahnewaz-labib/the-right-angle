main.exe: main.o menu.o connector.o
	g++ main.o menu.o connector.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

menu.o: menu.cpp menu.h
	g++ -std=c++11 -c menu.cpp

connector.o: connector.cpp connector.h
	g++ -std=c++11 -c connector.cpp


clean:
	rm *.o
	rm *.exe
