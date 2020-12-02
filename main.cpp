#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>
#include <SFML/Graphics.hpp>
#define GAME_WINDOW_WIDTH 500
#define GAME_WINDOW_HEIGHT 500

#define NUMBER_OF_OPTIONS 3

bool MENU_STATE = true;

using namespace sf;
using namespace std;

class Menu {
public:
    Menu(float menuWidth, float menuHeight);
    // ~Menu();

    void show(RenderWindow &menuWindow);
    void goUp();
    void goDown();

private:
    Font menuTextFont;
    Text menuText[NUMBER_OF_OPTIONS];
};

Menu::Menu(float menuWidth, float menuHeight) {
    menuTextFont.loadFromFile("fonts/12th_C._Fancy_Caps.ttf");
    
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

}

int main() {
    
    // Main game window
    RenderWindow gameWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "The Right Angle!");

    // Menu window
    // Menu menuWindow(300, 300);
    Menu menuWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

    while(gameWindow.isOpen()) {
        // To capture keypresses
        sf::Event e;
        
        // Handle KB or Mouse actions
        while(gameWindow.pollEvent(e)) {
            if(e.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Q)) {
                gameWindow.close();
            }
            if(MENU_STATE == true && Keyboard::isKeyPressed(Keyboard::Return)) {
                MENU_STATE = false;
            }
            if(MENU_STATE == false && Keyboard::isKeyPressed(Keyboard::Escape)) {
                MENU_STATE = true;
            }

            // if(Keyboard::isKeyPressed(Keyboard::Return)) {
            //     MENU_STATE = !MENU_STATE;
            // }
        }

        if(MENU_STATE) gameWindow.clear(Color::Black);
        else gameWindow.clear(Color::Cyan);

        if(MENU_STATE) menuWindow.show(gameWindow);

        gameWindow.display();

    }

    cout<<"Hi there"<<"\n";

    return 0;
}
