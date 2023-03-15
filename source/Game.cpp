#include "Game.h"

Game* Game::game = nullptr;

Game::Game()
{
    this->game = this;
    m_uiManager = nullptr;
    m_world = nullptr;
    m_inputManager = nullptr;
    m_scoreLifeManager = nullptr;
    int m_actualGameLevel = -1;
    bool m_quitGame = false;

}

Game::~Game()
{
    delete m_uiManager;

    delete m_world;

    delete m_inputManager;

}

void Game::update() {

    const float deltaTime = m_clock.restart().asSeconds();

    handleEvents();
    
    if (!m_window.isOpen() || m_quitGame == true) 
    {
        m_quitGame = true;
        return;
    }

    //Update world and uiManager
    m_world->update(deltaTime);
    m_uiManager->update(deltaTime);
   
    //Draw all
    m_window.clear();
    m_window.draw(m_background);
    m_world->draw(m_window);
    m_uiManager->draw(m_window);
    m_window.display();
    
}

void Game::init()
{
    //Init the necessary values
    m_font = sf::Font();
    m_actualGameLevel = 1;
    m_quitGame = false;

    //Create the window
    m_window.create(sf::VideoMode(1920, 1080), "Space Invaders");
    m_window.setFramerateLimit(60);

    //Create the uiManager ç, world, inputManager and the ScoreLife with the new, because we want to call it out the stack and we need to survive
    this->m_uiManager = new UIManager();

    this->m_world = new World();

    this->m_inputManager = new InputManager();

    this->m_scoreLifeManager = new ScoreLifeManager();

    //Add Player to the World
    Player* p = new Player();
    p->setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y-150));
    m_world->addObject(p);

    //Add Enemies to the World
    EnemySpawner* e =new EnemySpawner();
    e->want_to_spawn();
    m_world->addObject(e);


    //Load the font for all the game
    if (!m_font.loadFromFile("../Assets/Fonts/dogica.ttf"))
    {
        // error...
    }

    //Initialize the background of the game
    sf::Texture* t = new sf::Texture();
    t->loadFromFile("../Assets/Sprites/Fondo.png");
    TextureLoader::addTexture("background", t);
    m_background.setTexture(*TextureLoader::getTexture("background"));

}

void Game::handleEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

    }
}


bool Game::wantsToQuitGame()
{
    return m_quitGame;
}


UIManager* Game::getUIManager()
{
    return m_uiManager;
}

sf::RenderWindow* Game::getWindow()
{
    return &m_window;
}

sf::Font* Game::getFont()
{
    return &m_font;
}



World* Game::getWorld()
{
    return m_world;
}

InputManager* Game::getInputManager()
{
    return m_inputManager;
}

ScoreLifeManager* Game::getScoreLifeManager()
{
    return m_scoreLifeManager;
}

const int Game::getLevel()
{
    return m_actualGameLevel;
}

void Game::setQuitGame(bool quitGame)
{
    m_quitGame = quitGame;
}

Game* Game::getInstance()
{
    return game;
}

void Game::incrementLevel()
{
    m_actualGameLevel += 1;
};



