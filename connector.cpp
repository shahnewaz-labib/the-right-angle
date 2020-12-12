#include <SFML/Graphics.hpp>
#include "connector.h"
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

