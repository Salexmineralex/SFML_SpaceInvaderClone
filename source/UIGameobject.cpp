#include "UIGameobject.h"

UIGameobject::UIGameobject(sf::Vector2f position) :
    mIsMarkedForDeletion(false)
{
    sf::Transformable::setPosition(position);
}
UIGameobject::UIGameobject() :
    mIsMarkedForDeletion(false)
{
    sf::Transformable::setPosition(sf::Vector2f(0, 0));
}

bool UIGameobject::isMarkedForDeletion() const
{
    return mIsMarkedForDeletion;
}

void UIGameobject::setVisibility(const bool visibility)
{
    mVisibility = visibility;
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