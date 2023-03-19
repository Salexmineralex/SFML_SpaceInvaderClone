#include "Game.h"

Game* Game::game = nullptr;

Game::Game()
{
    this->game = this;
    m_uiManager = nullptr;
    m_world = nullptr;
    m_GameOverWindow = nullptr;
    m_inputManager = nullptr;
    m_scoreLifeManager = nullptr;
    int m_actualGameLevel = -1;
    bool m_quitGame = false;
    bool m_gameOver = false;
    std::ifstream f("../Assets/data.json");
    data = new json();
    f >> *data;

}

Game::~Game()
{
    delete m_uiManager;

    delete m_world;

    delete m_inputManager;

    delete data;

}

void Game::update() {

    const float deltaTime = m_clock.restart().asSeconds();

    handleEvents();
    
    if (!m_window.isOpen() || m_quitGame == true) 
    {
        m_quitGame = true;
        return;
    }


    switch (m_Gamestate)
    {
    case START:

        break;
    case GAME:
        //Update world and uiManager
        m_world->update(deltaTime);
        m_uiManager->update(deltaTime);

        //Draw all
        m_window.clear();
        m_window.draw(m_background);
        m_world->draw(m_window);
        m_uiManager->draw(m_window);
        break;
    case GAMEOVER:
        title = sf::Text("Game Over", *getFont(), 80);
        title.setFillColor(sf::Color::Green);
        title.setPosition(m_window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100);

        // Create score text
        score = sf::Text("Your score:" + getScoreLifeManager()->getScore(), *getFont(), 40);
        score.setFillColor(sf::Color::Green);
        score.setPosition(m_window.getSize().x / 2 - score.getGlobalBounds().width / 2, 250);

        // Create replay button
        replayButton = sf::RectangleShape(sf::Vector2f(200, 50));
        replayButton.setPosition(m_window.getSize().x / 2 - replayButton.getSize().x / 2, 400);
        replayButton.setFillColor(sf::Color::Green);

        // Create replay button text
        replayButtonText = sf::Text("R for replay || ESC to quit", *getFont(), 40);
        replayButtonText.setFillColor(sf::Color::White);
        replayButtonText.setPosition(replayButton.getPosition().x + replayButton.getSize().x / 2 - replayButtonText.getGlobalBounds().width / 2, replayButton.getPosition().y + replayButton.getSize().y / 2 - replayButtonText.getGlobalBounds().height / 2);

        m_window.clear(sf::Color::Black);

        // Draw title text
        m_window.draw(title);

        // Draw score text
        m_window.draw(score);

        // Draw replay button
        m_window.draw(replayButton);
        m_window.draw(replayButtonText);

        if (Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::R))
        {
            Game::init();
            m_Gamestate = GAME;
        }
        if (Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::Escape))
        {
            
            m_quitGame = true;
            delete this;
        }
        /*m_GameOverWindow->update(deltaTime);
        m_window.clear();
        m_GameOverWindow->draw(m_window);*/
        break;
    default:
        break;
    }

    m_window.display();
}

void Game::init()
{
    //Init the necessary values
    m_font = sf::Font();
    m_actualGameLevel = getData()["Game"]["level"];
    m_quitGame = false;
    //Create the window
    m_window.create(sf::VideoMode(getData()["Game"]["window"]["width"], getData()["Game"]["window"]["height"]), "Space Invaders");
    m_window.setFramerateLimit(getData()["Game"]["framerate"]);

    //Create the uiManager ç, world, inputManager and the ScoreLife with the new, because we want to call it out the stack and we need to survive
    this->m_uiManager = new UIManager();

    this->m_world = new World();

    this->m_inputManager = new InputManager();

    this->m_scoreLifeManager = new ScoreLifeManager();

    this->m_GameOverWindow = new GameOverWindow();

    //Add Player to the World
    Player* p = new Player();
    p->setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y-150));
    m_world->addObject(p);

    //Add Enemies to the World
    EnemySpawner* e =new EnemySpawner();
    e->want_to_spawn();
    m_world->addObject(e);


    //Load the font for all the game
    if (!m_font.loadFromFile(getData()["Game"]["fontPath"]))
    {
        // error...
    }

    //Initialize the background of the game
    sf::Texture* t = new sf::Texture();
    t->loadFromFile(getData()["Game"]["backgroundPath"]);
    TextureLoader::addTexture("background", t);
    m_background.setTexture(*TextureLoader::getTexture("background"));

    m_Gamestate = GAME;

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

json Game::getData()
{
    return *this->data;
}

const int Game::getLevel()
{
    return m_actualGameLevel;
}

void Game::setQuitGame(bool quitGame)
{
    m_quitGame = quitGame;
}

void Game::setGameOver(bool gameOver)
{
    m_Gamestate = GAMEOVER;
}

Game* Game::getInstance()
{
    return game;
}

void Game::incrementLevel()
{
    m_actualGameLevel += getData()["Game"]["increment_every_level"];
};



/* sf::Text title("Game Over", *getFont(), 80);
        title.setFillColor(sf::Color::Green);
        title.setPosition(m_window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100);

        // Create score text
        sf::Text score("Your score:"+getScoreLifeManager()->getScore(), *getFont(), 40);
        score.setFillColor(sf::Color::Green);
        score.setPosition(m_window.getSize().x / 2 - score.getGlobalBounds().width / 2, 250);

        // Create replay button
        sf::RectangleShape replayButton(sf::Vector2f(200, 50));
        replayButton.setPosition(m_window.getSize().x / 2 - replayButton.getSize().x / 2, 400);
        replayButton.setFillColor(sf::Color::Green);

        // Create replay button text
        sf::Text replayButtonText("Replay", *getFont(), 40);
        replayButtonText.setFillColor(sf::Color::White);
        replayButtonText.setPosition(replayButton.getPosition().x + replayButton.getSize().x / 2 - replayButtonText.getGlobalBounds().width / 2, replayButton.getPosition().y + replayButton.getSize().y / 2 - replayButtonText.getGlobalBounds().height / 2);

        m_window.clear(sf::Color::Black);

        // Draw title text
        m_window.draw(title);

        // Draw score text
        m_window.draw(score);

        // Draw replay button
        m_window.draw(replayButton);
        m_window.draw(replayButtonText);

        m_window.display();*/