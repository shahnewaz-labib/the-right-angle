#include <SFML/Graphics.hpp>
#include "menu.h"
#include "connector.h"

#define GAME_WINDOW_WIDTH 500
#define GAME_WINDOW_HEIGHT 500

bool MENU_STATE = true;
bool GAME_STATE = false;
bool KEY_PRESSED = false;

using namespace sf;


int main() {
    
    // Main game window
    RenderWindow gameWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "The Right Angle!");

    // Menu window
    Menu menuWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

    while(gameWindow.isOpen()) {
        // To capture keypresses
        Event event;
        
        // Handle KB or Mouse actions
        while(gameWindow.pollEvent(event)) {

            if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Q)) {
                gameWindow.close();
            }

            if(MENU_STATE) {
                if(Keyboard::isKeyPressed(Keyboard::Return)) {

                    switch(menuWindow.selectedOptionIndex) {
                        case 0:
                            // Plat button pressed, enter game state
                            MENU_STATE = false;
                            GAME_STATE = true;
                            break;
                        case 2:
                            // Exit button pressed, close game
                            gameWindow.close();
                            break;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)) {
                    menuWindow.goUp();
                }
                if(Keyboard::isKeyPressed(Keyboard::Down)) {
                    menuWindow.goDown();
                }

            }
            
            // Esc pressed, return to menu state
            if(GAME_STATE == true && Keyboard::isKeyPressed(Keyboard::Escape)) {
                MENU_STATE = true;
                GAME_STATE = false;
            }
            
        }

        if(MENU_STATE) gameWindow.clear(Color::Black);
        else gameWindow.clear(Color::Cyan);

        if(MENU_STATE) menuWindow.show(gameWindow);

        gameWindow.display();

    }

    return 0;
}
