#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "ObjectPooler.h"
#include <vector>
#include "world.h"
#include "Enemy.h"
#include "game.h"
class EnemySpawner : public Gameobject {
public:

    //Constructors
    EnemySpawner(World& world, sf::RenderWindow& m_window);

    //GetAndSetters
    virtual std::string getTag() const;

    //Methods
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void createText(std::string str);
    void createCountdown(float dt);
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);

    void update(float dt) override;
    void want_to_spawn();
    bool isMarkedForDeletion() const;


private:

    // Atributos
    float enemydeltaClock = 0;
    float countdowndeltaClock = 0;
    bool move_down = false;
    bool move_to_left = false;
    bool have_to_spawn = false;
    std::vector<Enemy*> enemyGrid;
    World& m_world;
    sf::RenderWindow& m_window;
    ObjectPooler<Enemy> enemyPool;
    //Methods
    void spawn(int level);

    void deleteObjects();

    void CheckLost();


};