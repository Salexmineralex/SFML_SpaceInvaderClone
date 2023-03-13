#include <SFML/Graphics.hpp>
#include <gameobject.h>
#include "ObjectPooler.h"
#pragma once

class Bullet : public Gameobject {
public:

    //Constructors
    Bullet();


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

private:
    static int vecescreadaunabala;

    // Atributos
    sf::Sprite m_sprite;

    sf::Texture* m_texture;

    //Methods

};