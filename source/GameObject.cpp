#include "gameobject.h"

Gameobject::Gameobject(sf::Vector2f position) :
    m_IsMarkedForDeletion(false)
{
    sf::Transformable::setPosition(position);
}
Gameobject::Gameobject() :
    m_IsMarkedForDeletion(false)
{
    sf::Transformable::setPosition(sf::Vector2f(0,0));
}

void Gameobject::update(float dt)
{
    // Default implementation does nothing
}



void Gameobject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

bool Gameobject::collidesWith(const Gameobject& other) const
{
    
    return false;
}

void Gameobject::handleCollision(Gameobject& other)
{

}

bool Gameobject::isMarkedForDeletion() const
{
    return m_IsMarkedForDeletion;
}

void Gameobject::setVisibility(const bool visibility)
{
    Gameobject::m_Visibility = visibility;
}

void Gameobject::setPosition(sf::Vector2f position)
{
    sf::Transformable::setPosition(position);
}

sf::Vector2f Gameobject::getPosition() const
{
    return sf::Transformable::getPosition();
}

void Gameobject::updateAnimation()
{
}

