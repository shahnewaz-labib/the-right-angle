#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "menu.h"
#include <string>

using namespace sf;

#define addEntry(MenuText,Fn,clr,caption,x,y){ \
    MenuText.setFont(Fn); \
    MenuText.setColor(clr); \
    MenuText.setString(caption); \
    MenuText.setPosition(Vector2f(x,y)); \
}

Menu::Menu(float menuWidth, float menuHeight) {
#ifdef __linux__
    menuTextFont.loadFromFile("fonts/mrsmonsterital.ttf");
#else
    menuTextFont.loadFromFile("fonts\\mrsmonsterital.ttf");
#endif
    selectedOptionIndex = 0;
    int x=50,y=100;

    addEntry(menuText[0],menuTextFont, Color::Red, menucaption[0] , x, y);

    addEntry(LevelText, menuTextFont, Color::White, "Level : Random", x+ 170, y);


    for(int i = 1; i < NUMBER_OF_OPTIONS; i++){
        y += 70;
        addEntry(menuText[i], menuTextFont, Color::White, menucaption[i], x, y);
    } 
    addEntry(musicVolumeText,menuTextFont, Color::White, "Volume : 50%", x+170, y-70*1);
}

void Menu::musictoggle(sf::Music &music){
    musicState^=1;
    extern bool musicIsPlaying;
    if(musicState){
        menuText[2].setString("Music : ON");
        musicIsPlaying=1;
        music.play();
    } else {
        menuText[2].setString("Music : OFF");
        musicIsPlaying=0;
        music.stop();
    }
}



void Menu::levelup(){
    currentlevel = (currentlevel + 1) % totallevels;
    if(currentlevel==0){
        LevelText.setString("Level : Random");
    } else {
        LevelText.setString("Level : " + std::to_string(currentlevel));
    }    
}


void Menu::leveldown(){
    currentlevel = (currentlevel - 1+totallevels) % totallevels;
    if(currentlevel==0){
        LevelText.setString("Level : Random");
    } else {
        LevelText.setString("Level : " + std::to_string(currentlevel));
    }    
}
void Menu::volup(sf::Music &music){
    if(currentvol==90) 
        currentvol=100;
    else
        currentvol=(currentvol+10)%100;
    music.setVolume(currentvol); 
    musicVolumeText.setString("Volume : "+std::to_string(currentvol)+"%");
}
void Menu::voldown(sf::Music &music){
    if(currentvol==10)
        currentvol=100;
    else
        currentvol=(currentvol-10+100)%100;
    music.setVolume(currentvol); 
    musicVolumeText.setString("Volume : "+std::to_string(currentvol)+"%");
}



void Menu::show(RenderWindow &menuWindow) {
    for(int i = 0; i < NUMBER_OF_OPTIONS; i++) {
        menuWindow.draw(menuText[i]);
    }
    menuWindow.draw(LevelText);
    menuWindow.draw(musicVolumeText);
}


void Menu::goDown() {
    menuText[selectedOptionIndex].setColor(Color::White);
    selectedOptionIndex=(selectedOptionIndex+1)%NUMBER_OF_OPTIONS;
    menuText[selectedOptionIndex].setColor(Color::Red);
}

void Menu::goUp() {
    menuText[selectedOptionIndex].setColor(Color::White);
    selectedOptionIndex=(selectedOptionIndex+NUMBER_OF_OPTIONS-1)%NUMBER_OF_OPTIONS;
    menuText[selectedOptionIndex].setColor(Color::Red);
}


