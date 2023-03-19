#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "TextureLoader.h"
#include "Enemy.h"
#include "EnemyBullet.h"
class ShootingEnemy : public Enemy {
public:

    //Constructors
    ShootingEnemy();

    static ObjectPooler<EnemyBullet>* m_EnemybulletObjectPool;

    //GetandSetters
    const sf::Texture* getTexture();
    const sf::Sprite getSprite();
    std::string getTag() const;

    //Methods
    void move(float offsetX, float offsetY) override;
    void update(float dt) override;


    bool collidesWith(const Gameobject& other)  const override;

    void handleCollision(Gameobject& other) override;
  
    void updateAnimation() override;
  
private:

    // Atributos
    std::mt19937 rng;
    int m_score;
    float m_timeToShootdeltaClock = 0;

    enum ENEMY_ANIMATION_STATES { IDLE, IDLE_2 };


    //CONST VARIABLES
    const float m_SPECIAL_OBJECT_SPAWN_RATE = 0;

};