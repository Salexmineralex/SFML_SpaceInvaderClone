#include "Bullet.h"
#include <iostream>
#include "TextureLoader.h"
#include "Player.h"
#include "Game.h"

Bullet::Bullet():
    m_BULLET_SPEED(Game::getInstance()->getData()["Bullet"]["bulletSpeed"])
{

    TextureLoader t;
    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile(Game::getInstance()->getData()["Bullet"]["texturePath"]))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }
  


    this->setPosition(Game::getInstance()->getData()["Bullet"]["position"][0], Game::getInstance()->getData()["Bullet"]["position"][1]);
    this->setOrigin(Game::getInstance()->getData()["Bullet"]["origin"][0], Game::getInstance()->getData()["Bullet"]["origin"][1]);

    m_sprite.setPosition(sf::Vector2f(Game::getInstance()->getData()["Bullet"]["position"][0], Game::getInstance()->getData()["Bullet"]["position"][1]));
    m_sprite.setOrigin(Game::getInstance()->getData()["Bullet"]["origin"][0], Game::getInstance()->getData()["Bullet"]["origin"][1]);
    m_sprite.setTexture(*this->m_texture);
    m_currentframe.width = Game::getInstance()->getData()["Bullet"]["currentFrame"]["width"];
    m_currentframe.height = Game::getInstance()->getData()["Bullet"]["currentFrame"]["height"];
    m_sprite.setTextureRect(m_currentframe);
    m_animState = IDLE;

}

Bullet::~Bullet()
{
    delete m_texture;
}



const sf::Texture* Bullet::getTexture()
{
    return this->m_texture;
}

const sf::Sprite Bullet::getSprite()
{
    return this->m_sprite;
}
std::string Bullet::getTag() const
{
    return "Bullet";
}
;

void Bullet::setPosition(float x, float y)
{

    sf::Transformable::setPosition(x, y);
    m_sprite.setPosition(getPosition());
}

// Override the move function to update the sprite's position
void Bullet::move(float x, float y)
{

    sf::Transformable::setPosition(this->getPosition().x + x, this->getPosition().y + y);
    m_sprite.setPosition(getPosition());


}


void Bullet::update(float dt)
{
      if (getPosition().y <= -10 && !m_IsMarkedForDeletion)
      {
          resetBullet();
      }
      else
      {
          move(0, -(m_BULLET_SPEED * dt));
      
      }

      updateAnimation();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    //states.transform = getTransform();
    if(this->m_Visibility)
    {
        target.draw(m_sprite, states);
    }
   
}


bool Bullet::collidesWith(const Gameobject& other) const
{
   
    if(this->m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds()))
    {
        return true;
    }

    return false;
};

void Bullet::handleCollision(Gameobject& other)
{
    if(other.getTag() == "Enemy" || other.getTag() == "ShootingEnemy")
    {
        resetBullet();
    }
}

void Bullet::updateAnimation()
{

    if (this->m_animTimer.getElapsedTime().asSeconds() >= 0.2f && m_animState != PROPF)
    {
        switch (m_animState)
        {
        case IDLE: 
            m_animState = PROP;
            m_currentframe.top = 0;
            m_currentframe.left = 0;
            m_sprite.setTextureRect(m_currentframe);
            break;
        case PROP: 
            m_animState = PROP2;
            m_currentframe.top = 0;
            m_currentframe.left += 25;
            m_sprite.setTextureRect(m_currentframe);
            break;
        case PROP2:
            m_animState = PROPF;
            m_currentframe.top = 0;
            m_currentframe.left += 25;
            m_sprite.setTextureRect(m_currentframe);
            break;
        default:
            break;
        }

        m_animTimer.restart();
    }

}

void Bullet::resetBullet()
{

    this->setPosition(0, 0);
    this->setVisibility(false);
    m_currentframe.top = 0;
    m_currentframe.left = 0;
    m_animState = IDLE;
    m_sprite.setTextureRect(m_currentframe);
    this->m_IsMarkedForDeletion = true;
    Player::m_bulletObjectPool->add_one(this);

};

bool Bullet::isMarkedForDeletion() const
{
    return Gameobject::m_IsMarkedForDeletion;
}