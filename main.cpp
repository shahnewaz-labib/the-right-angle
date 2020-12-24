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

//Connector grid[MAX][MAX];
int n;
// Connector& cell(sf::Vector2i v) {
//     return grid[v.x][v.y];
// }

// bool isOut(sf::Vector2i v, int N) {
//     return !sf::IntRect(0, 0, N, N).contains(v);
// }

// void generate(int N) {
//     std::vector<sf::Vector2i> nodes;
//     nodes.push_back(sf::Vector2i(rand()%N, rand()%N));

//     while(!nodes.empty()) {
//         int n = rand()%nodes.size();
//         sf::Vector2i v = nodes[n];
//         sf::Vector2i d = DIR[rand()%4];

//         if(cell(v).dirs.size() == 3) {
//             nodes.erase(nodes.begin() + n);
//             continue;
//         }

//         if(cell(v).dirs.size() == 2) {
//             if(rand()%50) continue;
//         }

//         bool complete = true;
//         for(int i = 0; i < 4; i++) {
//             sf::Vector2i D = DIR[i];
//             if(!isOut(v + D, N) and cell(v + D).dirs.empty()) {
//                 complete = false;
//                 break;
//             }
//         }

//         if(complete) {
//             nodes.erase(nodes.begin() + n);
//             continue;
//         }

//         if(isOut(v + d, N)) continue;

//         if(!cell(v + d).dirs.empty()) continue;

//         cell(v).dirs.push_back(d);
//         cell(v+d).dirs.push_back(-d);

//         nodes.push_back(v+d);
//     }

// }

// void show(int n) {
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             std::cout << grid[i][j].dirs.size() << " ";
//         }
//         std::cout << "\n";
//     }
// }


int main() {
    oikhane:
    // Main game window
    RenderWindow menuWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "The Right Angle!");
    menuWindow.setKeyRepeatEnabled(false);

    // Menu window
    Menu menu(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

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

    while(menuWindow.isOpen()) {
        // To capture keypresses
        Event event;
        
        // Handle KB or Mouse actions
        while(menuWindow.pollEvent(event)) {

            if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Q)) {
                menuWindow.close();
                exit(0);
            }

            if(MENU_STATE) {
                if(event.type == Event::KeyReleased) {
                    if(event.key.code == Keyboard::Return) {
                        switch(menu.selectedOptionIndex) {
                            case OPTION_INDEX::Play:
                                // Play button pressed, enter game state
                                MENU_STATE = false;
                                GAME_STATE = true;
                                menuWindow.close();
                                goto sheshe;
                                break;
                            case OPTION_INDEX::Change_Level:
                                // Added level cycling
                                menu.levelup();
                                break;
                            case OPTION_INDEX::Options:
                                // Do something cool
                                break;
                            case OPTION_INDEX::Exit:
                                // Exit button pressed, close game
                                menuWindow.close();
                                exit(0);
                                break;
                            default:
                                break;
                        }
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)) {
                    menuOptionsSound.play();
                    menu.goUp();
                }
                if(Keyboard::isKeyPressed(Keyboard::Down)) {
                    menuOptionsSound.play();
                    menu.goDown();
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
            menuWindow.clear(Color::Black);
        }
        else if(GAME_STATE) {
            menuWindow.clear(Color::Cyan);
            // draw background
            menuWindow.draw(bgSprite);
        }
        if(MENU_STATE) {
            menu.show(menuWindow);
        }

        menuWindow.display();

    }

    sheshe:
    RenderWindow gameWindow(VideoMode(65*n, 65*n), "The Right Angle!");
    n = rand()%10+4;
    generate(n);
    
    show(n);

    gameWindow.setKeyRepeatEnabled(false);
    while(gameWindow.isOpen()) {
        Event event;
        while(gameWindow.pollEvent(event)) {
            if(event.type == Event::Closed)
                gameWindow.close();
            if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                MENU_STATE = true;
                GAME_STATE = false;
                gameWindow.close();
                goto oikhane;
            }
            if(event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                    // now, if any tile is clicked, see the changes it made i.e. update the orientation
                    // of the connectors
            }
                
        }
        // gameWindow.clear(Color::Green);
        gameWindow.draw(bgSprite);
        gameWindow.display();
    }

    return 0;
}
