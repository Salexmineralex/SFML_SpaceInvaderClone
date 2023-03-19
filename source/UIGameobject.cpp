#include "UIGameobject.h"

UIGameobject::UIGameobject(sf::Vector2f position) :
    m_IsMarkedForDeletion(false)
{
    sf::Transformable::setPosition(position);
}
UIGameobject::UIGameobject() :
    m_IsMarkedForDeletion(false)
{
    sf::Transformable::setPosition(sf::Vector2f(0, 0));
}

bool UIGameobject::isMarkedForDeletion() const
{
    return m_IsMarkedForDeletion;
}

void UIGameobject::setVisibility(const bool visibility)
{
    m_Visibility = visibility;
}

void UIGameobject::setPosition(sf::Vector2f position)
{
    sf::Transformable::setPosition(position);
}

void UIGameobject::setOrigin(sf::Vector2f position)
{
    sf::Transformable::setOrigin(position);
}

sf::Vector2f UIGameobject::getPosition() const
{
    return sf::Transformable::getPosition();
}