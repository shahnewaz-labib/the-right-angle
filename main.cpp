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


int main() {
    
    // Main game window
    RenderWindow gameWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "The Right Angle!");

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
                            // Play button pressed, enter game state
                            MENU_STATE = false;
                            GAME_STATE = true;
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
            
            // Esc pressed, return to menu state
            if(GAME_STATE) {
                if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                    MENU_STATE = true;
                    GAME_STATE = false;
                }
                if(event.type == Event::MouseButtonPressed) {
                    clickSound.play();
                }

            }
            
        }

        if(MENU_STATE) gameWindow.clear(Color::Black);
        else gameWindow.clear(Color::Cyan);

        if(MENU_STATE) menuWindow.show(gameWindow);

        gameWindow.display();

    }

    return 0;
}
