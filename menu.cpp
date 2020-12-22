#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "menu.h"
#include <string>

using namespace sf;

#define addEntry(MenuText,Fn,clr,caption,x,y){ \
    MenuText.setFont(Fn); \
    MenuText.setColor(clr); \
    MenuText.setString(caption); \
    MenuText.setPosition(Vector2f(x,y)); \
}

Menu::Menu(float menuWidth, float menuHeight) {
    menuTextFont.loadFromFile("fonts/3Dumb.ttf");
    selectedOptionIndex = 0;
    int x=50,y=100;

    addEntry(menuText[0],menuTextFont, Color::Red, menucaption[0] , x, y);

    addEntry(LevelText, menuTextFont, Color::White, "Level : "+levels[0] , x+170, y);

    for(int i=1;i<NUMBER_OF_OPTIONS;i++){
        y+=70;
        addEntry(menuText[i],menuTextFont,Color::White,menucaption[i],x,y);
    } 
}



void Menu::levelup(){
    currentlevel=(currentlevel+1)%totallevels;
    LevelText.setString("Level : " + levels[currentlevel]);    
}



void Menu::show(RenderWindow &menuWindow) {
    for(int i = 0; i < NUMBER_OF_OPTIONS; i++) {
        menuWindow.draw(menuText[i]);
    }
    menuWindow.draw(LevelText);
}


void Menu::goDown() {
    menuText[selectedOptionIndex].setColor(Color::White);
    selectedOptionIndex=(selectedOptionIndex+1)%NUMBER_OF_OPTIONS;
    menuText[selectedOptionIndex].setColor(Color::Red);
}

void Menu::goUp() {
    menuText[selectedOptionIndex].setColor(Color::White);
    selectedOptionIndex=(selectedOptionIndex+NUMBER_OF_OPTIONS-1)%NUMBER_OF_OPTIONS;
    menuText[selectedOptionIndex].setColor(Color::Red);
}


