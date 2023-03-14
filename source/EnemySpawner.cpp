#include "enemySpawner.h"

EnemySpawner::EnemySpawner(World& world, sf::RenderWindow& window):
    m_world(world),
    m_window(window)   
{
    
    this->enemyGrid = std::vector<Enemy*>();
    this->enemyPool = ObjectPooler<Enemy>(10);
    this->my_countdown_text = new MyText();
    createText();
    Game::getUIManager()->addObject(my_countdown_text);
    
}

std::string EnemySpawner::getTag() const
{
    return "EnemySpawner";
}


void EnemySpawner::update(float dt)
{
    deleteObjects();
    CheckLost();
    
    if (enemydeltaClock >= 3.6609*exp(-0.199*Game::getLevel() ))
    {
        
        if (move_down)
        {
            for (int i = 0; i < enemyGrid.size(); i++)
            {
             
                enemyGrid[i]->move(0, 100);

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
        Game::incrementLevel();
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
        for (size_t i = 0; i < 2 * level; i++)
        {

            Enemy* p = this->enemyPool.get_one();
            p->mIsMarkedForDeletion = false;
            p->setVisibility(true);
            m_world.addObject(p);
            p->setPosition(sf::Vector2f((m_window.getSize().x/2 - p->getTexture()->getSize().x) - p->getTexture()->getSize().x * colum * 2.5, line));

            enemyGrid.push_back(p);



            Enemy* g = this->enemyPool.get_one();
            g->mIsMarkedForDeletion = false;
            g->setVisibility(true);
            m_world.addObject(g);
            g->setPosition(sf::Vector2f((m_window.getSize().x / 2 + p->getTexture()->getSize().x) + p->getTexture()->getSize().x * colum * 2.5, line));

            enemyGrid.push_back(g);

            colum++;

            if (p->getPosition().x <= 250)
            {
                /*    Enemies p = Enemies();
                    p.setPosition(400 - (p.getTexture()->getSize().x * 2.5 * colum + 1), line);
                    enemies.push_back(p);*/

                line += p->getTexture()->getSize().y * 2;
                colum = 0;
            }

         }


   
};

void EnemySpawner::deleteObjects()
{
    auto it = enemyGrid.begin();
    while (it != enemyGrid.end()) {
        if ((*it)->isMarkedForDeletion()) {
            
            enemyPool.add_one(*it);
            it = enemyGrid.erase(it); // Remove object from vector
        }
        else {
            ++it;
        }
    }
}

void EnemySpawner::CheckLost()
{
    for (int i = 0; i < enemyGrid.size(); i++)
    {
        if (enemyGrid[i]->getPosition().y >= m_window.getSize().y - 150)
        {
            std::cout << "Lost";
        }
    }
}

bool EnemySpawner::isMarkedForDeletion() const
{
    return Gameobject::mIsMarkedForDeletion;
}


void EnemySpawner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   /* for (size_t i = 0; i < enemyGrid.size(); i++)
    {
        enemyGrid[i]->draw(m_window,states);
    }*/
    
}

void EnemySpawner::createText()
{


    my_countdown_text->getText()->setFont(*Game::getFont());

    my_countdown_text->getText()->setCharacterSize(100);

    my_countdown_text->getText()->setFillColor(sf::Color::Green);


    my_countdown_text->getText()->setStyle(sf::Text::Bold);


    //text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);

    my_countdown_text->setPosition(m_window.getView().getCenter());
    my_countdown_text->setOrigin(sf::Vector2f(my_countdown_text->getText()->getGlobalBounds().width, my_countdown_text->getText()->getGlobalBounds().height / 2.f));
 
}

void EnemySpawner::createCountdown(float dt)
{

    if (dt <= 4 && have_to_spawn)
    {
        my_countdown_text->setVisibility(true);
        if (dt < 1)
        {
            
            my_countdown_text->getText()->setString("Level" + std::to_string(Game::getLevel()));
        }
        else
        {
            int seconds = (static_cast<int>(dt));
            my_countdown_text->getText()->setString(std::to_string(seconds));
        }

    }
    else if (have_to_spawn)
    {
      
        spawn(Game::getLevel());
        have_to_spawn = false;
        my_countdown_text->setVisibility(false);
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


