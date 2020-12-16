#include <vector>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "variables.h"
#include "menu.h"
#include "connector.h"
#include "game.h"

using namespace sf;

int main() {
    oikhane:
    // Main game window
    RenderWindow gameWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "The Right Angle!");
    gameWindow.setKeyRepeatEnabled(false);

    // Menu window
    Menu menuWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

    // Sound
    SoundBuffer clickSoundBuffer;
    clickSoundBuffer.loadFromFile("sounds/logout.ogg");
    Sound clickSound;
    clickSound.setBuffer(clickSoundBuffer);

    SoundBuffer menuOptionsSoundBuffer;
    menuOptionsSoundBuffer.loadFromFile("sounds/roblox-death-sound_1.ogg");
    Sound menuOptionsSound;
    menuOptionsSound.setBuffer(menuOptionsSoundBuffer);

    // Textures
    Texture background;
    background.loadFromFile("background.jpg");

    // Sprites
    Sprite bgSprite;
    bgSprite.setTexture(background);

    //* sprite.setTextureRect(sf::IntRect(10, 10, 32, 32)); we can specify rect
    // bgSprite.setTextureRect(IntRect(0, 0, 612, 408));

    int n = rand()%10+2;
    generate(n);

    while(gameWindow.isOpen()) {
        // To capture keypresses
        Event event;
        
        // Handle KB or Mouse actions
        while(gameWindow.pollEvent(event)) {

            if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Q)) {
                gameWindow.close();
                exit(0);
            }
            

            if(MENU_STATE) {
                if(event.type == Event::KeyReleased) {
                    if(event.key.code == Keyboard::Return) {
                        switch(menuWindow.selectedOptionIndex) {
                            case 0:
                                // Play button pressed, enter game state
                                MENU_STATE = false;
                                GAME_STATE = true;
                                gameWindow.close();
                                goto sheshe;
                                break;
                            case 1:
                                // Added level cycling
                                menuWindow.levelup();
                                break;
                            case 2:
                                // Do something cool
                                break;
                            case 3:
                                // Exit button pressed, close game
                                gameWindow.close();
                                exit(0);
                                break;
                            default:
                                break;
                        }
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)) {
                    menuOptionsSound.play();
                    menuWindow.goUp();
                }
                if(Keyboard::isKeyPressed(Keyboard::Down)) {
                    menuOptionsSound.play();
                    menuWindow.goDown();
                }
                

            }
            
            if(GAME_STATE) {
                // Esc pressed, return to menu state
                if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                    MENU_STATE = true;
                    GAME_STATE = false;
                    goto sheshe;
                }
                

            }
            
        }
        if(MENU_STATE) {
            gameWindow.clear(Color::Black);
        }
        else if(GAME_STATE) {
            gameWindow.clear(Color::Cyan);
            // draw background
            gameWindow.draw(bgSprite);
        }
        if(MENU_STATE) {
            menuWindow.show(gameWindow);
        }

        gameWindow.display();

    }

    sheshe:
    RenderWindow w1(VideoMode(65*n, 65*n), "Another window");
    w1.setKeyRepeatEnabled(false);
    while(w1.isOpen()) {
        Event event;
        while(w1.pollEvent(event)) {
            if(event.type == Event::Closed)
                w1.close();
            if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                MENU_STATE = true;
                GAME_STATE = false;
                w1.close();
                goto oikhane;
            }
            if(event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                    // now, if any tile is clicked, see the changes it made i.e. update the orientation
                    // of the connectors
            }
                
        }
        // w1.clear(Color::Green);
        w1.draw(bgSprite);
        w1.display();
    }

    return 0;
}
