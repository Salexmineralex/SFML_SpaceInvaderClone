#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "TextureLoader.h"
class Enemy : public Gameobject {
public:

    //Constructors
    Enemy();
    


    //GetandSetters
    const sf::Texture* getTexture();
    const sf::Sprite getSprite();
    std::string getTag() const;

    //Methods
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPosition(sf::Vector2f position);
    void move(float offsetX, float offsetY);
    void update(float dt) override;
    bool isMarkedForDeletion() const;


private:

    // Atributos


    
};