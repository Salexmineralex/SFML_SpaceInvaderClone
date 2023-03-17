#include "player.h"
#include <TextureLoader.h>



//Constructores
ObjectPooler<Bullet>* Player::m_bulletObjectPool;


Player::Player():
    m_speed(1000)
{
    TextureLoader t;
    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile("../Assets/Sprites/Ship_Idle.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }


    this->setPosition(0, 0);
    this->setOrigin(0, 0);
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);
    this->m_bulletObjectPool = new ObjectPooler<Bullet>(3);
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

        if (!m_texture->loadFromFile("../Assets/Sprites/bulletSprite.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }



    this->setPosition(0, 0);
    this->setOrigin(0, 0);
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);
    this->m_bulletObjectPool = new ObjectPooler<Bullet>(3);
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

    if(Game::getInstance()->getScoreLifeManager()->getLife() <= 0)
    {
    
    }

    if(Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::Left) && getPosition().x > 0)
    {
        this->move(-getSpeed() * dt, 0.0f);
    }
    if(Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::Right) && getPosition().x < Game::getInstance()->getWindow()->getSize().x-m_texture->getSize().x)
    {
        this->move(getSpeed() * dt, 0.0f);
    }
    if (Game::getInstance()->getInputManager()->GetKeyPressed(sf::Keyboard::Space) && !isShooting)
    {
   
      
        isShooting = true;

        Bullet* b = m_bulletObjectPool->get_one();

        b->mIsMarkedForDeletion = false;

        b->setVisibility(true);
        
    

        b->setPosition(getPosition().x + b->getTexture()->getSize().x/4, getPosition().y-20);

        Game::getInstance()->getWorld()->addObject(b);

      

    }

    

    if(m_secondsToShoot >= 2)
    {
        isShooting = false;
        m_secondsToShoot = 0;
    }

    m_secondsToShoot += dt;


}
bool Player::isMarkedForDeletion() const
{
    return Gameobject::mIsMarkedForDeletion;
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
        std::cout << "OjetoSpecial";
    }


};

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->mVisibility)
    {
        target.draw(m_sprite, states);
    }
};