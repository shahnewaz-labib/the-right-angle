#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "menu.h"

using namespace sf;

Menu::Menu(float menuWidth, float menuHeight) {
    menuTextFont.loadFromFile("fonts/12th_C._Fancy_Caps.ttf");
    selectedOptionIndex = 0;

    menuText[0].setFont(menuTextFont);
    menuText[0].setColor(Color::Red);
    menuText[0].setString("Play");
    menuText[0].setPosition(Vector2f(menuWidth/2+140, menuHeight/2-200));

    menuText[1].setFont(menuTextFont);
    menuText[1].setColor(Color::White);
    menuText[1].setString("Options");
    menuText[1].setPosition(Vector2f(menuWidth/2+90, menuHeight/4));

    menuText[2].setFont(menuTextFont);
    menuText[2].setColor(Color::White);
    menuText[2].setString("Exit");
    menuText[2].setPosition(Vector2f(menuWidth/2+130, menuHeight/2.5));
}

void Menu::show(RenderWindow &menuWindow) {
    for(int i = 0; i < NUMBER_OF_OPTIONS; i++) {
        menuWindow.draw(menuText[i]);
    }
}

void Menu::goDown() {
    if(selectedOptionIndex + 1 < NUMBER_OF_OPTIONS) {
        menuText[selectedOptionIndex].setColor(Color::White);
        selectedOptionIndex++;
        menuText[selectedOptionIndex].setColor(Color::Red);
    }
}

void Menu::goUp() {
    if(selectedOptionIndex - 1 >= 0) {
        menuText[selectedOptionIndex].setColor(Color::White);
        selectedOptionIndex--;
        menuText[selectedOptionIndex].setColor(Color::Red);
    }
}
