_OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJ=$(patsubst %,obj/%,$(_OBJ))
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Program: $(OBJ)
	g++ $(OBJ) -o $@ $(LIBS)

obj/main.o: main.cpp
	g++ --std=c++17 -c main.cpp -o $@

obj/menu.o: menu.cpp menu.h
	g++ --std=c++17 -c menu.cpp -o $@

clean:
	rm $(OBJ)
