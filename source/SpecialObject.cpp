#include "SpecialObject.h"
#include <iostream>
#include "TextureLoader.h"
#include "Player.h"
#include "Game.h"

SpecialObject::SpecialObject()
{

    TextureLoader t;
    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile("../Assets/Sprites/powerUP_sprite.png"))
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

SpecialObject::~SpecialObject()
{
    delete m_texture;
}



const sf::Texture* SpecialObject::getTexture()
{
    return this->m_texture;
}

const sf::Sprite SpecialObject::getSprite()
{
    return this->m_sprite;
}
std::string SpecialObject::getTag() const
{
    return "SpecialObject";
}
;

void SpecialObject::setPosition(float x, float y)
{

    sf::Transformable::setPosition(x, y);
    m_sprite.setPosition(getPosition());
}

// Override the move function to update the sprite's position
void SpecialObject::move(float x, float y)
{

    sf::Transformable::setPosition(this->getPosition().x + x, this->getPosition().y + y);
    m_sprite.setPosition(getPosition());


}


void SpecialObject::update(float dt)
{
    if (getPosition().y >= 1000 && !m_IsMarkedForDeletion)
    {
        resetObject();
    }
    else
    {
        move(0, (200 * dt));

    }
}

void SpecialObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    //states.transform = getTransform();
    if (this->m_Visibility)
    {
        target.draw(m_sprite, states);
    }

}


bool SpecialObject::collidesWith(const Gameobject& other) const
{

    if (this->m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds()))
    {
        return true;
    }

    return false;
};

void SpecialObject::handleCollision(Gameobject& other)
{
    
}
void SpecialObject::resetObject()
{

    this->setPosition(0, 0);
    this->setVisibility(false);
    this->m_IsMarkedForDeletion = true;


};

bool SpecialObject::isMarkedForDeletion() const
{
    return Gameobject::m_IsMarkedForDeletion;
}