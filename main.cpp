#include <iostream>
#include <SFML/Graphics.hpp>

#define GAME_WINDOW_WIDTH 500
#define GAME_WINDOW_HEIGHT 500

using namespace sf;
using namespace std;

int main() {
    
    // Main game window
    RenderWindow gameWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "The Right Angle!");

    while(gameWindow.isOpen()) {
        // To capture keypresses
        sf::Event e;
        
        // Handle KB or Mouse actions
        while(gameWindow.pollEvent(e)) {
            if(e.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Q)) {
                gameWindow.close();
            }
        }

        gameWindow.clear(Color::Cyan);
        gameWindow.display();

    }



    return 0;
}
