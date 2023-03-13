#include "Game.h"

UIManager* Game::uiManager;
World* Game::world;
sf::Font font = sf::Font();
int Game::actualLevel = 1;
bool quitGame = false;

Game::Game()
{
}

void Game::run() {
    sf::Clock clock;
    //Init World
    sf::Texture t;
    t.loadFromFile("../Assets/Sprites/Fondo.png");
    sf::Sprite background(t);
    
    while (m_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        world->update(deltaTime);
        uiManager->update(deltaTime);
        handleEvents();
        m_window.clear();
        m_window.draw(background);
        world->draw();
        uiManager->draw();
        m_window.display();
    }
}

void Game::init()
{

    m_window.create(sf::VideoMode(1920, 1080), "Space Invaders");
    m_window.setFramerateLimit(60);

    this->uiManager = new UIManager(m_window);

    this->world = new World(m_window);

    //Add Player to the World
    Player* p = new Player(world->getInputManager(), *world, m_window);
    p->setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y-150));
    world->addObject(p);

    //Add Enemies to the World
    EnemySpawner* e =new EnemySpawner(*world, m_window);
    e->want_to_spawn();
    world->addObject(e);

    if (!font.loadFromFile("../Assets/Fonts/dogica.ttf"))
    {
        // error...
    }
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
    return quitGame;
}


UIManager* Game::getUIManager()
{
    return uiManager;
}

sf::Font Game::getFont()
{
    return font;
}



World* Game::getWorld()
{
    return world;
}

const int Game::getLevel()
{
    return actualLevel;
}

void Game::incrementLevel()
{
    actualLevel += 1;
};



