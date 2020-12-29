#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
// #include "variables.h"

#ifndef CONNECTOR
#define CONNECTOR

class Connector {
    public:
        std::vector<sf::Vector2i> dirs;
        // Connector();
        int orientation, angle;
        bool isConnected(sf::Vector2i);
        bool on;
        // void rotate();
        // void rotate() {
        //     for(int i = 0; i < dirs.size(); i++) {
        //         if(dirs[i] == UP) dirs[i] = Right;
        //         else if(dirs[i] == RIGHT) dirs[i] = Down;
        //         else if(dirs[i] == DOWN) dirs[i] = Left;
        //         else if(dirs[i] == LEFT) dirs[i] = Up;
        //     }
        // }


    private:

};




#endif
