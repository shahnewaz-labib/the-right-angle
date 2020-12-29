#include <SFML/Graphics.hpp>
#include "connector.h"
// #ifndef GLOBAL_VARIABLES
// #include "variables.h"
// #endif
// Connector::Connector() {
//     angle = 0;
//     // orientation = some_value;

// }

bool Connector::isConnected(sf::Vector2i dir)
{
    for(auto d: dirs)
     if (d==dir) return true;
    return false;
}

// void Connector::rotate() {
//     for(int i = 0; i < dirs.size(); i++) {
//         if(dirs[i] == Up) dirs[i] = Right;
//         else if(dirs[i] == Right) dirs[i] = Down;
//         else if(dirs[i] == Down) dirs[i] = Left;
//         else if(dirs[i] == Left) dirs[i] = Up;
//     }
// }

