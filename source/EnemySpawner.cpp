#include "enemySpawner.h"
EnemySpawner::EnemySpawner() 
{
    
    this->m_enemyGrid = std::vector<Enemy*>();
    this->m_enemyObjectPool = ObjectPooler<Enemy>(10);
    this->m_ShootingenemyObjectPool = ObjectPooler<ShootingEnemy>(5);
    this->m_countdown_text = new MyText();
    createText();

    Game::getInstance()->getUIManager()->addObject(m_countdown_text);
    
}

EnemySpawner::~EnemySpawner()
{
    delete m_countdown_text;
}

std::string EnemySpawner::getTag() const
{
    return "EnemySpawner";
}


void EnemySpawner::update(float dt)
{
    deleteObjects();
    CheckLost();
    
    if (m_enemydeltaClock >= 3.6609*exp(-0.199*Game::getInstance()->getLevel() ))
    {
        
        if (move_down)
        {
            for (int i = 0; i < m_enemyGrid.size(); i++)
            {
             
                m_enemyGrid[i]->move(0, 100);

            }
            move_down = false;

        }
        else if (!move_to_left)
        {
            
            for (int i = 0; i < m_enemyGrid.size(); i++)
            {
               
                m_enemyGrid[i]->move(35, 0);
                
                if (m_enemyGrid[i]->getPosition().x+ m_enemyGrid[i]->getTexture()->getSize().x > Game::getInstance()->getWindow()->getSize().x - m_enemyGrid[i]->getTexture()->getSize().x)
                {
                    move_to_left = true;
                    move_down = true;
                }
            }

        }
        else
        {

            for (int i = 0; i < m_enemyGrid.size(); i++)
            {


                m_enemyGrid[i]->move(-35, 0);
                
                if (m_enemyGrid[i]->getPosition().x < 0 + m_enemyGrid[i]->getTexture()->getSize().x)
                {
                    move_to_left = false;
                    move_down = true;
                }
            }

        }

        m_enemydeltaClock = 0;
    }

    if(m_enemyGrid.size() <= 0 && have_to_spawn == false)
    {
        Game::getInstance()->incrementLevel();
        this->want_to_spawn();
    }

    createCountdown(m_countdowndeltaClock);

    m_enemydeltaClock += dt;
    m_countdowndeltaClock += dt;
}

void EnemySpawner::spawn(int level)
{
        int line = 10;
        int colum = 0;


        //Spawn Enemies
        for (size_t i = 0; i < 2 * level; i++)
        {

            Enemy* p = nullptr;
            Enemy* g = nullptr;
            
            std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(1, 100);
            int randomNumber = uniformDistribution(rng);
            if(randomNumber <= Game::getInstance()->getLevel()* 4.9444f - 4.444f)
            {
                p = this->m_ShootingenemyObjectPool.get_one();
            }else
            {
                p = this->m_enemyObjectPool.get_one();
            }

            p->mIsMarkedForDeletion = false;
            p->setVisibility(true);
            Game::getInstance()->getWorld()->addObject(p);
            p->setPosition(sf::Vector2f((Game::getInstance()->getWindow()->getSize().x/2 - p->getTexture()->getSize().x) - p->getTexture()->getSize().x * colum * 2.5, line));

            m_enemyGrid.push_back(p);

            if (uniformDistribution(rng) <= Game::getInstance()->getLevel() * m_shootingEnemyPercentSpawn)
            {
                g = this->m_ShootingenemyObjectPool.get_one();
            }
            else
            {
                g = this->m_enemyObjectPool.get_one();
            }

            g->mIsMarkedForDeletion = false;
            g->setVisibility(true);
            Game::getInstance()->getWorld()->addObject(g);
            g->setPosition(sf::Vector2f((Game::getInstance()->getWindow()->getSize().x / 2 + p->getTexture()->getSize().x) + p->getTexture()->getSize().x * colum * 2.5, line));

            m_enemyGrid.push_back(g);

            colum++;

            if (p->getPosition().x <= 250)
            {

                line += p->getTexture()->getSize().y * 2;
                colum = 0;
            }

         }

    
   
};

void EnemySpawner::deleteObjects()
{
    auto it = m_enemyGrid.begin();
    while (it != m_enemyGrid.end()) {
        if ((*it)->isMarkedForDeletion()) {
            
            m_enemyObjectPool.add_one(*it);
            it = m_enemyGrid.erase(it); // Remove object from vector
        }
        else {
            ++it;
        }
    }
}

void EnemySpawner::CheckLost()
{
    for (int i = 0; i < m_enemyGrid.size(); i++)
    {
        if (m_enemyGrid[i]->getPosition().y >= Game::getInstance()->getWindow()->getSize().y - 150)
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


    m_countdown_text->getText()->setFont(*Game::getInstance()->getFont());

    m_countdown_text->getText()->setCharacterSize(100);

    m_countdown_text->getText()->setFillColor(sf::Color::Green);


    m_countdown_text->getText()->setStyle(sf::Text::Bold);


    //text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);

    m_countdown_text->setPosition(Game::getInstance()->getWindow()->getView().getCenter());
    m_countdown_text->setOrigin(sf::Vector2f(m_countdown_text->getText()->getGlobalBounds().width, m_countdown_text->getText()->getGlobalBounds().height / 2.f));
 
}

void EnemySpawner::createCountdown(float dt)
{

    if (dt <= 4 && have_to_spawn)
    {
        m_countdown_text->setVisibility(true);
        if (dt < 1)
        {
            
            m_countdown_text->getText()->setString("Level" + std::to_string(Game::getInstance()->getLevel()));
        }
        else
        {
            int seconds = (static_cast<int>(dt));
            m_countdown_text->getText()->setString(std::to_string(seconds));
        }

    }
    else if (have_to_spawn)
    {
      
        spawn(Game::getInstance()->getLevel());
        have_to_spawn = false;
        m_countdown_text->setVisibility(false);
    }
}

void EnemySpawner::want_to_spawn()
{
    this->have_to_spawn = true;

    m_countdowndeltaClock = 0;
};

void EnemySpawner::setPosition(float x, float y)
{
}

void EnemySpawner::move(float offsetX, float offsetY)
{
}


