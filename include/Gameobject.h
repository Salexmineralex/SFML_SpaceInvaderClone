#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include <chrono>
class Gameobject : public sf::Drawable, public sf::Transformable
{
public:

    //Constructor
    Gameobject(sf::Vector2f position);
    Gameobject();

    //Full Abstract Methods
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
    virtual std::string getTag() const = 0;
    virtual void setVisibility(const bool visibility);

    //Normal  virtual Methods

    virtual void update(float dt);
    virtual bool collidesWith(const Gameobject& other) const;
    virtual void handleCollision(Gameobject& other);
    virtual bool isMarkedForDeletion() const;

    //Methods
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;

    //Animation Methods
    virtual void updateAnimation();

    //Attributes
    bool m_IsMarkedForDeletion = false;
    bool m_Visibility = true;
    sf::Sprite m_sprite;
    sf::Texture* m_texture;

    //Animations
    int m_animState;
    sf::Clock m_animTimer;
    sf::IntRect m_currentframe;

};