#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "TextureLoader.h"
#include "player.h"
#include "enemySpawner.h"
#include "UIManager.h"
#include "ScoreLifeManager.h"
#include "GameOverWindow.h"
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;

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
    json getData();

   
    sf::Font* getFont();

    void incrementLevel();
    const int getLevel();
    void setQuitGame(bool quitGame);
    void setGameOver(bool gameOver);

    static Game* getInstance();


    //Methods
    bool wantsToQuitGame();




private:

    //Attributes
    sf::RenderWindow m_window;

    UIManager* m_uiManager;
    World* m_world;
    GameOverWindow* m_GameOverWindow;
    InputManager* m_inputManager;
    ScoreLifeManager* m_scoreLifeManager;

    sf::Clock m_clock;
    sf::Sprite m_background;
    sf::Font m_font;
    int m_actualGameLevel;
    int m_Gamestate;
    bool m_quitGame;
    json* data;

    enum GAME_STATES{START,GAME,GAMEOVER };

    //Instance
    static Game* game;

    //Methods
    void handleEvents();

    //GAME OVER -TODO::CHANGE IN THE FUTURE
    sf::Text title;
    sf::Text score;
    sf::Text replayButtonText;
    sf::RectangleShape replayButton;
};