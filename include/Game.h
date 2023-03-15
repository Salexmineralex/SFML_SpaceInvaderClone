#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "TextureLoader.h"
#include "player.h"
#include "enemySpawner.h"
#include "UIManager.h"
#include "ScoreLifeManager.h"

class Game {
public:
    //Constructor
    Game();
    ~Game();
    //Main~
    void update();
    void init();

    //GetAndSet
    sf::RenderWindow* getWindow();
    UIManager* getUIManager();
    World* getWorld();
    InputManager* getInputManager();
    ScoreLifeManager* getScoreLifeManager();
   
    sf::Font* getFont();

    void incrementLevel();
    const int getLevel();
    void setQuitGame(bool quitGame);

    static Game* getInstance();


    //Methods
    bool wantsToQuitGame();




private:

    //Attributes
    sf::RenderWindow m_window;

    UIManager* m_uiManager;
    World* m_world;
    InputManager* m_inputManager;
    ScoreLifeManager* m_scoreLifeManager;

    sf::Clock m_clock;
    sf::Sprite m_background;
    sf::Font m_font;
    int m_actualGameLevel;
    bool m_quitGame;

    //Instance
    static Game* game;

    //Methods
    void handleEvents();
};