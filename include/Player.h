#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "InputManager.h"
#include "world.h"
#include "Bullet.h"
#include "ObjectPooler.h"

class Player : public Gameobject {
public:

    //Constructors
 
    Player(InputManager* inputManager, World& world, sf::RenderWindow& window);
    Player(InputManager* inputManager, World& world, sf::RenderWindow& window ,float speed);

    static ObjectPooler<Bullet>* bulletPool;

    //GetandSetters
    const sf::Texture* getTexture();

    const sf::Sprite getSprite();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float getSpeed() const;

    bool getShooting() const;

    void setShooting(bool isShooting);

    void setSpeed(float newSpeed);

    std::string getTag() const;

    //Methods
    void update(float dt) override;
   
    bool isMarkedForDeletion() const ;

    void setPosition(float x, float y);

    void setPosition(sf::Vector2f position);

    void move(float offsetX, float offsetY);

    virtual bool collidesWith(const Gameobject& other) const override;
    virtual void handleCollision(Gameobject& other) override;

private:

    // Atributos
    float m_speed = 10000;
    float secondsToShoot = 0;
    bool isShooting = false;
    InputManager* m_InputManager;
    World& m_world;
    sf::RenderWindow& m_window;

 
};