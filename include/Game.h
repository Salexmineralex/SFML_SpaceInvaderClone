#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "TextureLoader.h"
#include "world.h"
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
    static void incrementLevel();
    static const int getLevel();
    //Methods
    bool wantsToQuitGame();
    void setQuitGame(bool quitGame);



private:
    void handleEvents();
    sf::RenderWindow m_window;
    static UIManager* uiManager;
    static World* world;
    static int actualLevel;

    bool quitGame = false;
};