#include <vector>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "variables.h"
#include "menu.h"
#include "connector.h"
#include "game.h"

using namespace sf;

int n;
int tileSize = 54;
Menu menu(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

// Sound
SoundBuffer clickSoundBuffer;
Sound clickSound;
SoundBuffer menuOptionsSoundBuffer, menuEnterPressSoundBuffer;
Sound menuOptionsSound, menuEnterPressSound;

// Texture
Texture bg, comp, server, pipes;

// Sprite
Sprite bgSprite, compSprite, serverSprite, pipesSprite;

Vector2f offset(65, 55);

void SHOW_MENU();

void SHOW_GAME()
{

    std::cout << "here\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grid[i][j].dirs.clear();
        }
    }
    if (menu.currentlevel == 0)
        n = rand() % 7 + 4;
    else
        n = menu.currentlevel + 4;
    RenderWindow gameWindow(VideoMode(65 * n, 65 * n), "The Right Angle!");

    Vector2u TextureSize = bg.getSize();
    Vector2u WindowSize = gameWindow.getSize();

    float ScaleX = (float)WindowSize.x / TextureSize.x;
    float ScaleY = (float)WindowSize.y / TextureSize.y;

    bgSprite.setScale(ScaleX, ScaleY); // Scaling the bg according to window size

    generate(n);

    show(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Connector &p = grid[i][j];
            for (int n = 4; n > 0; n--)
            {
                std::string s = "";
                for (auto d : DIR)
                    s += p.isConnected(d) ? "1" : "0";

                if (s == "0011" || s == "0111" || s == "0101" || "0010")
                    p.orientation = n;
                p.rotate();
                for (int n = 0; rand() % 4; n++)
                {
                    grid[i][j].orientation++;
                    grid[i][j].rotate();
                }
            }
        }
    }

    // Assign serverpos
    Vector2i servPos = Vector2i(rand() % n, rand() % n);
    while (node(servPos).dirs.size() == 1)
    {
        servPos = Vector2i(rand() % n, rand() % n);
    }

    serverSprite.setPosition(Vector2f(servPos * tileSize));
    serverSprite.move(offset);

    gameWindow.setKeyRepeatEnabled(false);
    while (gameWindow.isOpen())
    {
        Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Q))
            {
                gameWindow.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                menuEnterPressSound.play();

#ifdef __linux__
                usleep(1000000 / 5);
#elif _WIN32
                sleep(1000 / 5);
#endif

                MENU_STATE = true;
                GAME_STATE = false;
                gameWindow.close();
                SHOW_MENU();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                clickSound.play();
                // now, if any tile is clicked, see the changes it made i.e. update the orientation
                // of the connectors
                if (Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    Vector2i pos = Mouse::getPosition(gameWindow) + Vector2i(tileSize/2, tileSize/2) - Vector2i(offset);
                    pos = pos/tileSize;
                    if(isOutOfWindow(pos, n)) continue;
                    std::swap(pos.x, pos.y);
                    node(pos).orientation++;
                    node(pos).rotate();

                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            grid[i][j].on = false;
                        }
                    }

                    drop(servPos, n);
                }
            }
        }
        gameWindow.clear();
        gameWindow.draw(bgSprite);

        // Update the pipe images according to the new orientation
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Connector &p = grid[i][j];
                int kind = p.dirs.size();

                if (kind == 2 && p.dirs[0] == -p.dirs[1])
                    kind = 0;

                p.angle += 5;

                p.angle = std::min(p.angle, p.orientation * 90);

                pipesSprite.setTextureRect(IntRect(tileSize * kind, 0, tileSize, tileSize));
                pipesSprite.setRotation(p.angle);
                pipesSprite.setPosition(j * tileSize, i * tileSize);
                pipesSprite.move(offset);
                compSprite.move(offset);
                gameWindow.draw(pipesSprite);
            }
        }

        gameWindow.draw(serverSprite);
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
        menuWindow.display();
    }
}

void init()
{
    // Sound
    clickSoundBuffer.loadFromFile("sounds/click.ogg");
    clickSound.setBuffer(clickSoundBuffer);

    menuOptionsSoundBuffer.loadFromFile("sounds/menuClick.wav");
    menuEnterPressSoundBuffer.loadFromFile("sounds/enterPressed.wav");
    menuOptionsSound.setBuffer(menuOptionsSoundBuffer);
    menuEnterPressSound.setBuffer(menuEnterPressSoundBuffer);

    // Textures
    bg.loadFromFile("images/background.png");
    comp.loadFromFile("images/comp.png");
    server.loadFromFile("images/server.png");
    pipes.loadFromFile("images/pipes.png");
    pipes.setSmooth(1);
    // Sprites
    bgSprite.setTexture(bg);
    compSprite.setTexture(comp);
    serverSprite.setTexture(server);
    pipesSprite.setTexture(pipes);
    pipesSprite.setOrigin(27, 27);
    serverSprite.setOrigin(20, 20);
    compSprite.setOrigin(18, 18);
    //* sprite.setTextureRect(sf::IntRect(10, 10, 32, 32)); we can specify rect
    // bgSprite.setTextureRect(IntRect(0, 0, 612, 408));
}

int main()
{
    srand(time(0));
    init();
    SHOW_MENU();
    return 0;
}
