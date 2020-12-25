#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "variables.h"
#include "menu.h"
#include "connector.h"
#include "game.h"

using namespace sf;

int n;
Menu menu(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

SoundBuffer clickSoundBuffer;
Sound clickSound;
SoundBuffer menuOptionsSoundBuffer, menuEnterPressSoundBuffer;
Sound menuOptionsSound, menuEnterPressSound;
Texture background;
Sprite bgSprite;

void SHOW_MENU();

void SHOW_GAME()
{
    std::cout << "here\n";
    n = rand() % 10 + 2;
    RenderWindow gameWindow(VideoMode(65 * n, 65 * n), "The Right Angle!");
    // if(menu.currentlevel == 0) n = rand()%10+4;
    // else n = menu.currentlevel*3;
    // std::cout << n << "\n";
    generate(n);

    show(n);

    gameWindow.setKeyRepeatEnabled(false);
    while (gameWindow.isOpen())
    {
        Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Q))
            {
                // usleep(1000000); // in microseconds
                gameWindow.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                menuEnterPressSound.play();
                usleep(1000000 / 5);
                // std::cout << "here\n";
                MENU_STATE = true;
                GAME_STATE = false;
                gameWindow.close();
                //goto oikhane;
                SHOW_MENU();

            }
            if (event.type == Event::MouseButtonPressed)
            {
                clickSound.play();
                // now, if any tile is clicked, see the changes it made i.e. update the orientation
                // of the connectors
            }
        }
        // gameWindow.clear(Color::Green);
        gameWindow.draw(bgSprite);
        gameWindow.display();
    }
}

void SHOW_MENU()
{
    // Main game window
    RenderWindow menuWindow(VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "The Right Angle!");
    menuWindow.setKeyRepeatEnabled(false);

    while (menuWindow.isOpen())
    {
        // To capture keypresses
        Event event;

        // Handle KB or Mouse actions
        while (menuWindow.pollEvent(event))
        {

            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Q))
            {
                menuWindow.close();
                exit(0);
            }

            if (MENU_STATE)
            {
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == Keyboard::Return)
                    {
                        switch (menu.selectedOptionIndex)
                        {
                        case OPTION_INDEX::Play:
                            // Play button pressed, enter game state
                            MENU_STATE = false;
                            GAME_STATE = true;
                            menuWindow.close();
                            //goto sheshe;
                            SHOW_GAME(); //
                            return;
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
                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    menuOptionsSound.play();
                    menu.goUp();
                }
                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    menuOptionsSound.play();
                    menu.goDown();
                }
                if (Keyboard::isKeyPressed(Keyboard::Return))
                {
                    // menuOptionsSound.play();
                    if (menu.selectedOptionIndex != 3)
                        menuEnterPressSound.play();
                }
            }

            if (GAME_STATE)
            {
                // Esc pressed, return to menu state
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    MENU_STATE = true;
                    GAME_STATE = false;

                    SHOW_GAME();
                }
            }
        }
        if (MENU_STATE)
        {
            menuWindow.clear(Color::Black);
        }
        
        if (MENU_STATE)
        {
            menu.show(menuWindow);
        }
        // std::cout << menu.currentlevel << "\n";
        menuWindow.display();
    }
}

void init() {
    // Sound
    clickSoundBuffer.loadFromFile("sounds/click.ogg");
    clickSound.setBuffer(clickSoundBuffer);

    menuOptionsSoundBuffer.loadFromFile("sounds/menuClick.wav");
    menuEnterPressSoundBuffer.loadFromFile("sounds/enterPressed.wav");
    menuOptionsSound.setBuffer(menuOptionsSoundBuffer);
    menuEnterPressSound.setBuffer(menuEnterPressSoundBuffer);

    // Textures
    background.loadFromFile("images/background.jpg");

    // Sprites
    bgSprite.setTexture(background);

    //* sprite.setTextureRect(sf::IntRect(10, 10, 32, 32)); we can specify rect
    // bgSprite.setTextureRect(IntRect(0, 0, 612, 408));
}

int main()
{
    srand(time(0));

    // Menu window

    init();

    //

    // oikhane:
    SHOW_MENU();

    // sheshe:

    return 0;
}
