#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "TextureLoader.h"
#include "SpecialObject.h"
#include <random>
class Enemy : public Gameobject {
public:

    //Constructors
    Enemy();
    ~Enemy();


    //GetandSetters
    const sf::Texture* getTexture();
    const sf::Sprite getSprite();
    std::string getTag() const;

    //Methods
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPosition(sf::Vector2f position);
    virtual void move(float offsetX, float offsetY);
    void update(float dt) override;
    bool isMarkedForDeletion() const;

    bool collidesWith(const Gameobject& other) const override;
    void handleCollision(Gameobject& other) override;

    virtual void updateAnimation() override;

private:

    // Atributos
    std::mt19937 rng;
    int m_score;
    enum ENEMY_ANIMATION_STATES {IDLE, IDLE_2};


    //CONST VARIABLES
    const float m_SPECIAL_OBJECT_SPAWN_RATE = 0;
    
};