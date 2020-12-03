#pragma once

#ifndef MENU
#define MENU
#include <SFML/Graphics.hpp>


#define NUMBER_OF_OPTIONS 3

class Menu {
public:
    Menu(float menuWidth, float menuHeight);
    // ~Menu();

    void show(sf::RenderWindow &menuWindow);
    void goUp();
    void goDown();
    int selectedOptionIndex;
private:
    sf::Font menuTextFont;
    sf::Text menuText[NUMBER_OF_OPTIONS];
};

#endif
