#pragma once
#include <SFML/Graphics.hpp>

class UIGameobject : public sf::Drawable, public sf::Transformable
{
public:

    //Constructor
    UIGameobject(sf::Vector2f position);
    UIGameobject();

    //Full Abstract Methods
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;

    virtual std::string getTag() const = 0;
 

    //Normal  virtual Methods
    virtual bool isMarkedForDeletion() const;
    virtual void setVisibility(const bool visibility);
    //Methods
    virtual void setPosition(sf::Vector2f position);
    virtual void setOrigin(sf::Vector2f position);
    sf::Vector2f getPosition() const;

    //Attributes
    bool m_IsMarkedForDeletion = false;
    bool m_Visibility = true;

};