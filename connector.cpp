#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "connector.h"
#include <iostream>
// #ifndef GLOBAL_VARIABLES
// #endif
Connector::Connector() {
    angle = 0;
    // orientation = some_value;

}

bool Connector::isConnected(sf::Vector2i dir)
{
    for(auto d: dirs)
     if (d==dir) return true;
    return false;
}
extern sf::Vector2i DIR[4];
extern sf::Vector2i Up,Down,Right,Left;
void Connector::rotate() {
    for(int i = 0; i < dirs.size(); i++) {
        if(dirs[i] == Up) dirs[i] = Right;
        else if(dirs[i] == Right) dirs[i] = Down;
        else if(dirs[i] == Down) dirs[i] = Left;
        else if(dirs[i] == Left) dirs[i] = Up;
    }
}

