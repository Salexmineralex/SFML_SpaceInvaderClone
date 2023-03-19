#include "player.h"
#include <TextureLoader.h>



//Constructores
ObjectPooler<Bullet>* Player::m_bulletObjectPool;


Player::Player():
    m_speed(Game::getInstance()->getData()["Player"]["speed"]),
    m_TIME_TO_RESHOOT(Game::getInstance()->getData()["Player"]["time_to_reshoot"]),
    m_POWERUP_DURATION(Game::getInstance()->getData()["Player"]["power_up_duration"]),
    m_POWERUP_SPAWN_RATE(Game::getInstance()->getData()["Player"]["power_up_spawnrate"])
{
    
    TextureLoader t;
    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile(Game::getInstance()->getData()["Player"]["texturePath"]))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }


    this->setPosition(Game::getInstance()->getData()["Player"]["position"][0], Game::getInstance()->getData()["Player"]["position"][1]);
    this->setOrigin(Game::getInstance()->getData()["Player"]["origin"][0], Game::getInstance()->getData()["Player"]["origin"][1]);
    m_sprite.setPosition(sf::Vector2f(Game::getInstance()->getData()["Player"]["position"][0], Game::getInstance()->getData()["Player"]["position"][1]));
    m_sprite.setOrigin(Game::getInstance()->getData()["Player"]["origin"][0], Game::getInstance()->getData()["Player"]["origin"][1]);
    m_sprite.setTexture(*this->m_texture);
    this->m_bulletObjectPool = new ObjectPooler<Bullet>(Game::getInstance()->getData()["Player"]["bulletObjectPoolSize"]);
    m_currentframe.width = Game::getInstance()->getData()["Player"]["currentFrame"]["width"];
    m_currentframe.height = Game::getInstance()->getData()["Player"]["currentFrame"]["height"];
}

Player::Player(float speed):
    m_speed(speed)
{
    TextureLoader t;
    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile(Game::getInstance()->getData()["Player"]["texturePath"]))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }


    this->setPosition(Game::getInstance()->getData()["Player"]["position"][0], Game::getInstance()->getData()["Player"]["position"][1]);
    this->setOrigin(Game::getInstance()->getData()["Player"]["origin"][0], Game::getInstance()->getData()["Player"]["origin"][1]);
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);
    this->m_bulletObjectPool = new ObjectPooler<Bullet>(Game::getInstance()->getData()["Player"]["bulletObjectPoolSize"]);
    m_currentframe.width = Game::getInstance()->getData()["Player"]["currentFrame"]["width"];
    m_currentframe.height = Game::getInstance()->getData()["Player"]["currentFrame"]["height"];
}

Player::~Player()
{
    delete m_texture;
    delete m_bulletObjectPool;
 
}

float Player::getSpeed() const
{
    return this->m_speed;
}

bool  Player::getShooting() const
{
    return this->isShooting;
};

void  Player::setShooting(bool isShooting)
{
    this->isShooting = isShooting;
};

void  Player::setSpeed(float newSpeed)
{
    this->m_speed = newSpeed;
}
std::string Player::getTag() const
{
    return "Player";
}
void Player::update(float dt)
{
    m_animState = IDLE;
    if(Game::getInstance()->getScoreLifeManager()->getLife() <= 0)
    {
        Game::getInstance()->setGameOver(true);
    }

    if(Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::Left) && getPosition().x > 0)
    {
        this->move(-getSpeed() * dt, 0.0f);
        m_animState = LEFT;
    }
    if(Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::Right) && getPosition().x < Game::getInstance()->getWindow()->getSize().x-m_currentframe.width)
    {
        this->move(getSpeed() * dt, 0.0f);
        m_animState = RIGHT;
    }
    if (Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::Space) && !isShooting || m_powerUp && !isShooting)
    {
      
        isShooting = true;

        Bullet* b = m_bulletObjectPool->get_one();

        b->m_IsMarkedForDeletion = false;

        b->setVisibility(true);
        
        b->setPosition(getPosition().x + b->getTexture()->getSize().x/4, getPosition().y-20);

        Game::getInstance()->getWorld()->addObject(b);

        

    }

 

    if(m_secondsToShoot >= m_TIME_TO_RESHOOT || m_powerUp && m_secondsToShoot >= 0.2)
    {
        isShooting = false;
        m_secondsToShoot = 0;
    }

    if (m_powerUpTimer >= m_POWERUP_DURATION)
    {
        m_powerUp = false;
       
    }

    m_secondsToShoot += dt;
    m_powerUpTimer += dt;


    updateAnimation();
}
bool Player::isMarkedForDeletion() const
{
    return Gameobject::m_IsMarkedForDeletion;
}

void Player::setPosition(sf::Vector2f position)
{
    sf::Transformable::setPosition(position.x, position.y);
    m_sprite.setPosition(getPosition());
}

void Player::setPosition(float x, float y)
{

    sf::Transformable::setPosition(x, y);
    m_sprite.setPosition(getPosition());
}

// Override the move function to update the sprite's position
void Player::move(float x, float y)
{

    sf::Transformable::setPosition(this->getPosition().x + x, this->getPosition().y + y);
    m_sprite.setPosition(getPosition());


}

const sf::Texture* Player::getTexture()
{
    return this->m_texture;
}

const sf::Sprite Player::getSprite()
{
    return this->m_sprite;
}

bool Player::collidesWith(const Gameobject& other) const
{
    return false;
};
void Player::handleCollision(Gameobject& other)
{
    if(other.getTag() == "SpecialObject")
    {
        std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(1, 100);
        rng.seed((std::chrono::system_clock::now().time_since_epoch().count()));
        int randomNumber = uniformDistribution(rng);
        if(randomNumber <= m_POWERUP_SPAWN_RATE)
        {
            m_powerUp = true;
            m_powerUpTimer = 0;

        }else
        {
            Game::getInstance()->getScoreLifeManager()->addLife(10);
        }
        other.setPosition(sf::Vector2f(0, 0));
        other.setVisibility(false);
        other.m_IsMarkedForDeletion = true;

    }


}
void Player::updateAnimation()
{

    if(m_animState == IDLE)
    {
        m_currentframe.top = 0;
        m_currentframe.left = 0;
        m_sprite.setTextureRect(m_currentframe);
    } 
    if(m_animState == LEFT)
    {
        m_currentframe.top = 0;
        m_currentframe.left = 50;
        m_sprite.setTextureRect(m_currentframe);
    } 
    if(m_animState == RIGHT)
    {
        m_currentframe.top = 0;
        m_currentframe.left = 100;
        m_sprite.setTextureRect(m_currentframe);
    }


};

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->m_Visibility)
    {
        target.draw(m_sprite, states);
    }
};