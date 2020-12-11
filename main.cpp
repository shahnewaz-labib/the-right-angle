#include <vector>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "variables.h"
#include "menu.h"
#include "connector.h"


using namespace sf;

Connector grid[MAX][MAX];
Connector& cell(sf::Vector2i v) {
    return grid[v.x][v.y];
}

bool isOut(sf::Vector2i v, int N) {
    return !sf::IntRect(0, 0, N, N).contains(v);
}

void generate(int N) {
    std::vector<sf::Vector2i> nodes;
    nodes.push_back(sf::Vector2i(rand()%N, rand()%N));

    while(!nodes.empty()) {
        int n = rand()%nodes.size();
        sf::Vector2i v = nodes[n];
        sf::Vector2i d = DIR[rand()%4];

        if(cell(v).dirs.size() == 3) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(cell(v).dirs.size() == 2) {
            if(rand()%50) continue;
        }

        bool complete = true;
        for(int i = 0; i < 4; i++) {
            sf::Vector2i D = DIR[i];
            if(!isOut(v + D, N) and cell(v + D).dirs.empty()) {
                complete = false;
                break;
            }
        }

        if(complete) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(isOut(v + d, N)) continue;

        if(!cell(v + d).dirs.empty()) continue;

        cell(v).dirs.push_back(d);
        cell(v+d).dirs.push_back(-d);

        nodes.push_back(v+d);
    }

}

void show(int N) {
    for(int i = 0; i < N; i++, std::cout << std::endl) {
        for(int j = 0; j < N; j++) {
            std::cout << grid[i][j].dirs.size() << " ";
        }
    }
    std::cout << "----------------\n";
}


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
    background.loadFromFile("images\\background1.jpg");

    // Sprites
    Sprite bgSprite;
    bgSprite.setTexture(background);

    //* sprite.setTextureRect(sf::IntRect(10, 10, 32, 32)); we can specify rect

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
                if(Keyboard::isKeyPressed(Keyboard::Return)) {

                    switch(menuWindow.selectedOptionIndex) {
                        case 0:
                            // Play button pressed, enter game state
                            MENU_STATE = false;
                            GAME_STATE = true;
                            gameWindow.close();
                            goto sheshe;
                            break;
                        case 1:
                            // Do something cool
                            break;
                        case 2:
                            // Exit button pressed, close game
                            gameWindow.close();
                            break;
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
                if(event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                    // now, if any tile is clicked, see the changes it made i.e. update the orientation
                    // of the connectors

                }
                if(INIT) {
                    show(n);
                    INIT = false;
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
    RenderWindow w1(VideoMode(100*n, 100*n), "Another window");

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
        }
        w1.clear(Color::Green);
        w1.display();
    }

    return 0;
}
