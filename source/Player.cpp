#include "player.h"


//Constructores


Player::Player(InputManager* inputManager, World& world, sf::RenderWindow& window):
    m_speed(1000),
    m_InputManager(inputManager),
    m_world(world),
    m_window(window)
{
}

Player::Player(InputManager* inputManager, World& world, sf::RenderWindow& window, float speed):
    m_speed(speed),
    m_InputManager(inputManager),
    m_world(world),
    m_window(window)
{
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

    if(m_InputManager->GetKeyPressed(sf::Keyboard::Left) && getPosition().x > 0)
    {
        this->move(-getSpeed() * dt, 0.0f);
    }
    if(m_InputManager->GetKeyPressed(sf::Keyboard::Right) && getPosition().x < m_window.getSize().x-20)
    {
        this->move(getSpeed() * dt, 0.0f);
    }
    if (m_InputManager->GetKeyPressed(sf::Keyboard::Space) && !isShooting)
    {
      
         
        Bullet* b = new Bullet();

        b->setPosition(getPosition().x + b->getTexture()->getSize().x/4, getPosition().y-20);

        m_world.addObject(b);

        isShooting = true;

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
    Gameobject::setPosition(position);
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape p(20);
    p.setFillColor(sf::Color::Red);
    p.setPosition(Gameobject::getPosition());
    target.draw(p);
};