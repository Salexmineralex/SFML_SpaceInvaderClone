#include <SFML/Graphics.hpp>
#include <gameobject.h>
#include "ObjectPooler.h"
#pragma once

class SpecialObject : public Gameobject {
public:

    //Constructors
    SpecialObject();
    ~SpecialObject();

    //GetandSetters
    const sf::Texture* getTexture();
    const sf::Sprite getSprite();
    std::string getTag() const;

    //Methods
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isMarkedForDeletion() const;
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);

    bool collidesWith(const Gameobject& other) const override;
    void handleCollision(Gameobject& other) override;

    void resetObject();

private:


};