#pragma once
#include <SFML/Graphics.hpp>

class Gameobject : public sf::Drawable, public sf::Transformable
{
public:
    Gameobject(sf::Vector2f position);
    Gameobject();

    virtual void update(float dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;

    virtual bool collidesWith(const Gameobject& other) const;
    virtual void handleCollision(Gameobject& other);
    virtual bool isMarkedForDeletion() const;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;

    bool mIsMarkedForDeletion = false;

    virtual std::string getTag() const = 0;

};