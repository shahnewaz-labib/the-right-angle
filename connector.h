#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#ifndef CONNECTOR
#define CONNECTOR

class Connector {
    public:
        std::vector<sf::Vector2i> dirs;
        // Connector();
        int orientation, angle;
        bool isConnected();

    private:

};




#endif
