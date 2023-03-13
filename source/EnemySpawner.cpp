#include "enemySpawner.h"
#include <iostream>
EnemySpawner::EnemySpawner(World& world, sf::RenderWindow& window):
    m_world(world),
    m_window(window)   
{
    
    this->enemyGrid = std::vector<Enemy*>();
    this->enemyPool = ObjectPooler<Enemy>(10);
    
}

std::string EnemySpawner::getTag() const
{
    return "EnemySpawner";
}


void EnemySpawner::update(float dt)
{
    if (enemydeltaClock >= 3)
    {
        if (move_down)
        {
            for (int i = 0; i < enemyGrid.size(); i++)
            {
             
                enemyGrid[i]->move(0, 35);

            }
            move_down = false;

        }
        else if (!move_to_left)
        {
            
            for (int i = 0; i < enemyGrid.size(); i++)
            {
                enemyGrid[i]->move(35, 0);

                if (enemyGrid[i]->getPosition().x+ enemyGrid[i]->getTexture()->getSize().x > m_window.getSize().x - enemyGrid[i]->getTexture()->getSize().x)
                {
                    move_to_left = true;
                    move_down = true;
                }
            }

        }
        else
        {

            for (int i = 0; i < enemyGrid.size(); i++)
            {


                enemyGrid[i]->move(-35, 0);
                
                if (enemyGrid[i]->getPosition().x < 0 + enemyGrid[i]->getTexture()->getSize().x)
                {
                    move_to_left = false;
                    move_down = true;
                }
            }

        }

        enemydeltaClock = 0;
    }

    if(enemyGrid.size() <= 0 && have_to_spawn == false)
    {
  
        this->want_to_spawn();
    }

    createCountdown(countdowndeltaClock);

    enemydeltaClock += dt;
    countdowndeltaClock += dt;
}

void EnemySpawner::spawn(int level)
{
        int line = 10;
        int colum = 0;


        //Spawn Enemies
        for (size_t i = 0; i < 9 * level; i++)
        {

            Enemy* p = this->enemyPool.get_one();

            p->setPosition(sf::Vector2f(m_window.getSize().x/2 - p->getTexture()->getSize().x * colum * 2.5, line));

            enemyGrid.push_back(p);



            Enemy* g = this->enemyPool.get_one();
            g->setPosition(sf::Vector2f(m_window.getSize().x / 2 + p->getTexture()->getSize().x * colum * 2.5, line));

            enemyGrid.push_back(g);

            colum++;

            if (p->getPosition().x <= 150)
            {
                /*    Enemies p = Enemies();
                    p.setPosition(400 - (p.getTexture()->getSize().x * 2.5 * colum + 1), line);
                    enemies.push_back(p);*/

                line += p->getTexture()->getSize().y * 2;
                colum = 0;
            }

        }
   
};

bool EnemySpawner::isMarkedForDeletion() const
{
    return Gameobject::mIsMarkedForDeletion;
}


void EnemySpawner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i = 0; i < enemyGrid.size(); i++)
    {
        enemyGrid[i]->draw(m_window,states);
    }
    
}

void EnemySpawner::createText(std::string str)
{

    sf::Text* text = new sf::Text();

    sf::Font* font = new sf::Font();
    if (!font->loadFromFile("../Assets/Fonts/dogica.ttf"))
    {
        // error...
    }

    text->setFont(*font);

    text->setCharacterSize(100);

    text->setFillColor(sf::Color::Green);


    text->setStyle(sf::Text::Bold);


    //text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);
    text->setOrigin(text->getGlobalBounds().width, text->getGlobalBounds().height / 2.f);
    text->setPosition(m_window.getView().getCenter());

   
    text->setString(str);
    Game g;
    g.getUIManager()->addObject(text);

    
}

void EnemySpawner::createCountdown(float dt)
{

    if (dt <= 4 && have_to_spawn)
    {
        if (dt < 1)
        {
            Game g;
            createText("Level" + std::to_string(g.getLevel()));
        }
        else
        {
            int seconds = (static_cast<int>(dt));
            createText(std::to_string(seconds));
        }

    }
    else if (have_to_spawn)
    {
        Game g;
        spawn(g.getLevel());
        have_to_spawn = false;
    }
}

void EnemySpawner::want_to_spawn()
{
    this->have_to_spawn = true;

    countdowndeltaClock = 0;
};

void EnemySpawner::setPosition(float x, float y)
{
}

void EnemySpawner::move(float offsetX, float offsetY)
{
}


