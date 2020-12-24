g++ -std=c++11 -c connector.cpp
g++ -std=c++11 -c menu.cpp
g++ -std=c++11 -c main.cpp
g++ main.o menu.o connector.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
.\main.exe