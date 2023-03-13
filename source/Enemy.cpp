#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
    TextureLoader t;

    if(t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile("../Assets/Sprites/enemie_sprite.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }



    this->setPosition(sf::Vector2f(0,0));
    this->setOrigin(0, 0);
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);


    
}

const sf::Texture* Enemy::getTexture()
{
    return this->m_texture;
}

const sf::Sprite Enemy::getSprite()
{
    return this->m_sprite;
}
std::string Enemy::getTag() const
{
    return "Enemy";
}
;

void Enemy::setPosition(sf::Vector2f position)
{
 
    Gameobject::setPosition(position);
    m_sprite.setPosition(getPosition());
}

// Override the move function to update the sprite's position
void Enemy::move(float x, float y)
{

    Gameobject::setPosition(sf::Vector2f(this->getPosition().x + x, this->getPosition().y + y));
    m_sprite.setPosition(getPosition());
 
}

void Enemy::update(float dt)
{

    


}
bool Enemy::isMarkedForDeletion() const
{
    return Gameobject::mIsMarkedForDeletion;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->mVisibility)
    {
        target.draw(m_sprite, states);
    }
};