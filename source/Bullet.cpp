#include "Bullet.h"
#include <iostream>
#include "TextureLoader.h"
#include "Player.h"
#include "Game.h"




Bullet::Bullet()
{

    TextureLoader t;
    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile("../Assets/Sprites/Cohetes.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }
  


    this->setPosition(0, 0);
    this->setOrigin(0, 0);
  /*  this->m_AnimChanger.restart();
    this->m_animationSwitch = true;*/
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);


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
      if (getPosition().y <= -10 && !mIsMarkedForDeletion)
      {
          
          this->setPosition(0, 0);
          this->setVisibility(false);
          this->mIsMarkedForDeletion = true;
          Player::bulletPool->add_one(this);   
      }
      else
      {
          move(0, -(1000 * dt));
      
      }
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    //states.transform = getTransform();
    if(this->mVisibility)
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
    if(other.getTag() == "Enemy")
    {
        this->setPosition(0, 0);
        this->setVisibility(false);
        this->mIsMarkedForDeletion = true;
        Player::bulletPool->add_one(this);
        other.setPosition(sf::Vector2f(0, 0));
        other.setVisibility(false);
        other.mIsMarkedForDeletion = true;
        

    }
};

bool Bullet::isMarkedForDeletion() const
{
    return Gameobject::mIsMarkedForDeletion;
}