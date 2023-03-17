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
    //Anim Attributes
    //enum class BULLET_ENUM_STATES{IDLE,PROP,PROP2};
    //int m_CurrentAnim;
    //sf::Clock m_AnimChanger;
    //sf::IntRect m_actualFrame;
    //bool m_animationSwitch;

};