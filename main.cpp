#include <SFML/Window/Keyboard.hpp>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include <exception>
#include <stdexcept>
#include <time.h>
#include <iostream>
#include "menu.h"
#include "variables.h"
#define GAMEOVERTEXT "You have solved the puzzle!\nPress Esc to exit to main menu"
using namespace sf;
int N;
int ts = 54; //tile size
Vector2f offset(65, 55);

int active_client=0,clients=0;
Texture t1, t2, t3, t4, gameOverTexture, menuTexture;
Sprite sBackground, sComp, sServer, sConnector, sGameOver, sMenu;
Menu menu(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

// Sound
SoundBuffer clickSoundBuffer;
Sound clickSound;

SoundBuffer menuOptionsSoundBuffer, menuEnterPressSoundBuffer;
Sound menuOptionsSound, menuEnterPressSound;

SoundBuffer wowSoundBuffer;
Sound wowSound;

Music music;


sf::Text gameOverText;
sf::Font gameOverFont;


void init();
void game();
void SHOW_MENU();

struct Connector
{
    std::vector<Vector2i> dirs;
    int orientation;
    float angle;
    bool on;

    Connector() { angle = 0; }

    void rotate()
    {
        for (int i = 0; i < dirs.size(); i++)
            if (dirs[i] == Up)
                dirs[i] = Right;
            else if (dirs[i] == Right)
                dirs[i] = Down;
            else if (dirs[i] == Down)
                dirs[i] = Left;
            else if (dirs[i] == Left)
                dirs[i] = Up;
    }

    bool isConnect(Vector2i dir)
    {
        for (auto d : dirs)
            if (d == dir)
                return true;
        return false;
    }
};

Connector grid[20][20];
Connector &cell(Vector2i v) { return grid[v.x][v.y]; }
bool isOut(Vector2i v) { return !IntRect(0, 0, N, N).contains(v); }

void generatePuzzle(int N)
{
    std::vector<Vector2i> nodes;
    nodes.push_back(Vector2i(rand() % N, rand() % N));

    while (!nodes.empty())
    {
        int n = rand() % nodes.size();
        Vector2i v = nodes[n];
        Vector2i d = DIR[rand() % 4];

        if (cell(v).dirs.size() == 3)
        {
            nodes.erase(nodes.begin() + n);
            continue;
        }
        if (cell(v).dirs.size() == 2)
            if (rand() % 50)
                continue;

        bool complete = 1;
        for (auto D : DIR)
            if (!isOut(v + D) && cell(v + D).dirs.empty())
                complete = 0;
        if (complete)
        {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if (isOut(v + d))
            continue;
        if (!cell(v + d).dirs.empty())
            continue;
        cell(v).dirs.push_back(d);
        cell(v + d).dirs.push_back(-d);
        nodes.push_back(v + d);
    }
}

void drop(Vector2i v)
{
    if (cell(v).on){
        return;
    }
    cell(v).on = true;
    if(cell(v).dirs.size()==1) active_client++;
    for (auto d : DIR)
        if (!isOut(v + d))
            if (cell(v).isConnect(d) && cell(v + d).isConnect(-d))
                drop(v + d);
}

int main()
{
    srand(time(0));
    init();
    SHOW_MENU();
}

void game()
{
    if(menu.music)
        music.play();
    music.setLoop(true);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            grid[i][j].on = 0;
        }
    }

    if (menu.currentlevel == 0)
        N = rand() % totallevels + 4;
    else
        N = menu.currentlevel + 4;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!grid[i][j].dirs.empty())
                grid[i][j].dirs.clear();
        }
    }

    generatePuzzle(N);
    clients=0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            clients+=(grid[i][j].dirs.size()==1);
        }
    }
    // srand(time(0));

    RenderWindow app(VideoMode(N * 65, N * 65), "The Right Angle!");

    Vector2u TextureSize = t1.getSize();
    Vector2u WindowSize = app.getSize();

    float ScaleX = (float)WindowSize.x / TextureSize.x;
    float ScaleY = (float)WindowSize.y / TextureSize.y;

    sBackground.setScale(ScaleX, ScaleY); // Scaling the bg according to window size

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            Connector &p = grid[j][i];

            for (int n = 4; n > 0; n--) //find orientation//
            {
                std::string s = "";
                for (auto d : DIR)
                    s += p.isConnect(d) ? '1' : '0';
                if (s == "0011" || s == "0111" || s == "0101" || s == "0010")
                    p.orientation = n;
                p.rotate();
            }
            /*
            for (int n = 0; n < rand() % 4; n++) //shuffle//
            {
                grid[j][i].orientation++;
                grid[j][i].rotate();
            }
            */
        }

    Vector2i servPos;
    while (cell(servPos).dirs.size() == 1)
    {
        servPos = Vector2i(rand() % N, rand() % N);
    }
    sServer.setPosition(Vector2f(servPos * ts));
    sServer.move(offset);

    while (app.isOpen())
    {


        app.draw(sBackground);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                Connector &p = grid[j][i];

                int kind = p.dirs.size();
                if (kind == 2 && p.dirs[0] == -p.dirs[1])
                    kind = 0;

                p.angle += 5;
                if (p.angle > p.orientation * 90)
                    p.angle = p.orientation * 90;

                sConnector.setTextureRect(IntRect(ts * kind, 0, ts, ts));
                sConnector.setRotation(p.angle);
                sConnector.setPosition(j * ts, i * ts);
                sConnector.move(offset);
                app.draw(sConnector);

                if (kind == 1)
                {
                    if (p.on)
                        sComp.setTextureRect(IntRect(53, 0, 36, 36));
                    else
                        sComp.setTextureRect(IntRect(0, 0, 36, 36));
                    sComp.setPosition(j * ts, i * ts);
                    sComp.move(offset);
                    app.draw(sComp);
                }
            }

                    Event e;
                    while (app.pollEvent(e))
                    {
                        if (e.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Q))
                            app.close();

                        if (e.type == Event::MouseButtonPressed)
                            if (Mouse::isButtonPressed(Mouse::Left))
                            {
                                clickSound.play();
                                Vector2i pos = Mouse::getPosition(app) + Vector2i(ts / 2, ts / 2) - Vector2i(offset);
                                pos /= ts;
                                if (isOut(pos))
                                    continue;
                                cell(pos).orientation++;
                                cell(pos).rotate();

                                for (int i = 0; i < N; i++)
                                    for (int j = 0; j < N; j++)
                                        grid[j][i].on = 0;

                                active_client=0;
                                drop(servPos);
                                // Win state
                                if(active_client==clients){
                                    music.pause();
                                    // music.setLoop(false);
                                    wowSound.play();
//                                     std::cout<<"YASS"<<"\n";
                                    RenderWindow gameOverWindow(VideoMode(500, 500), "!!!GAME OVER!!!");
                                    sf::Clock clock;
                                    int cnt=0;

                                    while(gameOverWindow.isOpen()) {

                                        Event event;
                                        while(gameOverWindow.pollEvent(event)) {
                                            if(event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Q)) {
                                                gameOverWindow.close();
                                            }
                                        }
                                        cnt%=1000;
                                        cnt++;
                                        gameOverWindow.clear(Color::Black);
                                        if(cnt < 333) gameOverText.setColor(Color::Green); 
                                        else if(cnt < 666) gameOverText.setColor(Color::Red);
                                        else gameOverText.setColor(Color::Yellow);

                                        if(clock.getElapsedTime().asSeconds() >= 3) gameOverWindow.close();
                                        gameOverWindow.draw(sGameOver);
                                        gameOverWindow.draw(gameOverText);
                                        gameOverWindow.display();
                                    }
                                    music.play();
                                }
                            }
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            menuEnterPressSound.play();

            #ifdef __linux__
            //                 usleep(1000000 / 5);
            #elif _WIN32
            //                 sleep(1000 / 5);
            #endif

                            MENU_STATE = true;
                            GAME_STATE = false;
                            app.close();
                            SHOW_MENU();
                        }
                    }

        app.draw(sServer);
        app.display();



    }
}

void SHOW_MENU()
{
    music.stop();
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
                            game(); //
                            return;
                            break;
                        case OPTION_INDEX::Change_Level:
                            menuOptionsSound.play();
                            menu.levelup();
                            break;
                        case OPTION_INDEX::Options:
                            menu.musictoggle();
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
              
                if(Keyboard::isKeyPressed(Keyboard::Right)){
                    menuOptionsSound.play();
                    if(menu.selectedOptionIndex==OPTION_INDEX::Change_Level){
                        menu.levelup();
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Left)){
                    menuOptionsSound.play();
                    if(menu.selectedOptionIndex==OPTION_INDEX::Change_Level){
                        menu.leveldown();
                    }
                }

            }

        }
        if (MENU_STATE)
        {
            // menuWindow.clear(Color::Black);
            menuWindow.draw(sMenu);
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
    clickSoundBuffer.loadFromFile("sounds/click.ogg");
    clickSound.setBuffer(clickSoundBuffer);

    menuOptionsSoundBuffer.loadFromFile("sounds/menuClick.wav");
    menuEnterPressSoundBuffer.loadFromFile("sounds/enterPressed.wav");
    wowSoundBuffer.loadFromFile("sounds/wow.wav");
    menuOptionsSound.setBuffer(menuOptionsSoundBuffer);
    menuEnterPressSound.setBuffer(menuEnterPressSoundBuffer);
    wowSound.setBuffer(wowSoundBuffer);

    t1.loadFromFile("images/gameBG.jpg");
    t2.loadFromFile("images/comp.png");
    t3.loadFromFile("images/server.png");
    t4.loadFromFile("images/Connector.png");
    t4.setSmooth(true);

    gameOverTexture.loadFromFile("images/rsz_shei2.png");
    gameOverTexture.setSmooth(true);

    menuTexture.loadFromFile("images/menuBG.jpg");

    sBackground.setTexture(t1);
    sComp.setTexture(t2);
    sServer.setTexture(t3);
    sConnector.setTexture(t4);
    sGameOver.setTexture(gameOverTexture);
    sMenu.setTexture(menuTexture);

    sConnector.setOrigin(27, 27);
    sComp.setOrigin(18, 18);
    sServer.setOrigin(20, 20);

    gameOverFont.loadFromFile("fonts/mrsmonsterital.ttf");
    gameOverText.setFont(gameOverFont);

    gameOverText.setFont(gameOverFont); 
    gameOverText.setColor(Color::Green); 
    gameOverText.setOutlineColor(Color::White);
    gameOverText.setString(GAMEOVERTEXT); 
    gameOverText.setPosition(Vector2f(75, 10));

    music.openFromFile("sounds/bgmusic.wav");
    music.setVolume(50.f);
}

