#include "player.h"
#include <TextureLoader.h>



//Constructores
ObjectPooler<Bullet>* Player::bulletPool;


Player::Player(InputManager* inputManager, World& world, sf::RenderWindow& window):
    m_speed(1000),
    m_InputManager(inputManager),
    m_world(world),
    m_window(window)
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


    this->life_progress_bar = ProgressBar();
    this->life_progress_bar.setPosition(sf::Vector2f(225,m_window.getSize().y - 50));
    Game::getUIManager()->addObject(&life_progress_bar);
    this->setPosition(0, 0);
    this->setOrigin(0, 0);
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);
    this->bulletPool = new ObjectPooler<Bullet>(3);
}

Player::Player(InputManager* inputManager, World& world, sf::RenderWindow& window, float speed):
    m_speed(speed),
    m_InputManager(inputManager),
    m_world(world),
    m_window(window)
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
    this->bulletPool = new ObjectPooler<Bullet>(3);
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

    if(this->life_progress_bar.getPercentage() <= 0)
    {
    
    }

    if(m_InputManager->GetKeyPressed(sf::Keyboard::Left) && getPosition().x > 0)
    {
        this->move(-getSpeed() * dt, 0.0f);
    }
    if(m_InputManager->GetKeyPressed(sf::Keyboard::Right) && getPosition().x < m_window.getSize().x-m_texture->getSize().x)
    {
        this->move(getSpeed() * dt, 0.0f);
    }
    if (m_InputManager->GetKeyPressed(sf::Keyboard::Space) && !isShooting)
    {
        life_progress_bar.setPercentage(life_progress_bar.getPercentage() - 10);
      
        isShooting = true;

        Bullet* b = bulletPool->get_one();

        b->mIsMarkedForDeletion = false;

        b->setVisibility(true);

        b->setPosition(getPosition().x + b->getTexture()->getSize().x/4, getPosition().y-20);

        m_world.addObject(b);

      

    }

    

    if(secondsToShoot >= 2)
    {
        isShooting = false;
        secondsToShoot = 0;
    }

    secondsToShoot += dt;


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



};

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->mVisibility)
    {
        target.draw(m_sprite, states);
    }
};