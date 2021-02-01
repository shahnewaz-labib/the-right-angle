#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Text.hpp>
#ifndef MENU
#define MENU
#include <SFML/Graphics.hpp>

#define totallevels 8 // including random
#define NUMBER_OF_OPTIONS 4

class Menu {
public:
    Menu(float menuWidth, float menuHeight);
    // ~Menu();

    void show(sf::RenderWindow &menuWindow);
    void goUp();
    void goDown();
    void musictoggle(sf::Music &music);
    void levelup();
    void leveldown();
    void volup(sf::Music &music);
    void voldown(sf::Music &music);
    bool musicState=1;
    int selectedOptionIndex=0,currentlevel=0,currentvol=50;
    std::string menucaption[NUMBER_OF_OPTIONS]={"Play","Change Level","Music : ON","Exit"};

private:
    sf::Font menuTextFont;
    sf::Text menuText[NUMBER_OF_OPTIONS];
    sf::Text LevelText,musicVolumeText;
};

#endif
