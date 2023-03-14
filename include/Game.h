#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "TextureLoader.h"
#include "player.h"
#include "enemySpawner.h"
#include "UIManager.h"
#include "ProgressBar.h"

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
    static void setQuitGame(bool quitGame);


    //Methods
    bool wantsToQuitGame();




private:

    //Attributes
    sf::RenderWindow m_window;
    static UIManager* uiManager;
    static World* world;
    static sf::Font font;
    static int actualLevel;
    static bool m_quitGame;

    //Methods
    void handleEvents();
};