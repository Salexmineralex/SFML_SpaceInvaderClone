#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "TextureLoader.h"
#include "player.h"
#include "enemySpawner.h"
#include "UIManager.h"

class Game {
public:
    //Constructor
    Game();

    //Main~
    void run();
    void init();

    //GetAndSet
    
    static UIManager* getUIManager();
    static World* getWorld();
    static sf::Font* getFont();
    static void incrementLevel();
    static const int getLevel();
    //Methods
    bool wantsToQuitGame();




private:

    //Attributes
    sf::RenderWindow m_window;
    static UIManager* uiManager;
    static World* world;
    static sf::Font* font;
    static int actualLevel;
 


    //static bool quitGame;

    //Methods
    //static void setQuitGame(bool quitGame);
    void handleEvents();
};