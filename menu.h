#pragma once

#include <SFML/Graphics/Text.hpp>
#ifndef MENU
#define MENU
#include <SFML/Graphics.hpp>

#define totallevels 5
#define NUMBER_OF_OPTIONS 4

class Menu {
public:
    Menu(float menuWidth, float menuHeight);
    // ~Menu();

    void show(sf::RenderWindow &menuWindow);
    void goUp();
    void goDown();
    void musictoggle();
    void levelup();
    bool music=1;
    int selectedOptionIndex;
    //std::string currentleve;
    int currentlevel;
    std::string menucaption[NUMBER_OF_OPTIONS]={"Play","Change Level","Music : ON","Exit"};
    std::string levels[totallevels] = {"random", "1", "2", "3", "4"};

private:
    sf::Font menuTextFont;
    sf::Text menuText[NUMBER_OF_OPTIONS];
    sf::Text LevelText;
};

#endif
