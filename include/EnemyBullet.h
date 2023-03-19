#include <SFML/Graphics.hpp>
#include <gameobject.h>
#include "Bullet.h"
#include "ObjectPooler.h"
#pragma once

class EnemyBullet : public Bullet {
public:

    //Constructors
    EnemyBullet();
    ~EnemyBullet();

    //GetandSetters
    const sf::Texture* getTexture();
    const sf::Sprite getSprite();
    std::string getTag() const;

    //Methods
    void update(float dt) override;

    bool collidesWith(const Gameobject& other) const override;
    void handleCollision(Gameobject& other) override;

private:

    // Atributos
    void resetBullet();
    
    //CONST VARIABLES
    float m_BULLET_SPEED = 0;
    float m_DAMAGE = 0;

};