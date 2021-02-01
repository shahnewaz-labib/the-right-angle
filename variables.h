// #pragma once

#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES
#include <SFML/Graphics.hpp>

enum OPTION_INDEX {
    Play=0,Change_Level,Options,Exit //Play=0,Change_Level=1,..Exit=4
};
// Init
bool INIT = true;

// Window sizes
float GAME_WINDOW_WIDTH = 500;
float GAME_WINDOW_HEIGHT = 500;

// States
bool MENU_STATE = true;
bool GAME_STATE = false;
bool KEY_PRESSED = false;
bool musicIsPlaying = 0;
// Connector directions
sf::Vector2i Up( 0, -1);
sf::Vector2i Down( 0, 1);
sf::Vector2i Right( 1, 0);
sf::Vector2i Left( -1, 0);
sf::Vector2i DIR[4] = { Up, Right, Down, Left};

// Grid sizes
const int MAX = 20;

#endif
