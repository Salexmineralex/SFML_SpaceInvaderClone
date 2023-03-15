#pragma once
#include <SFML/Graphics.hpp>
#include "MyText.h"
#include "gameobject.h"
#include "ObjectPooler.h"
#include <vector>
#include "world.h"
#include "Enemy.h"
#include "game.h"
#include <iostream>
#include <math.h>
class EnemySpawner : public Gameobject {
public:

    //Constructors
    EnemySpawner();
    ~EnemySpawner();
    //GetAndSetters
    virtual std::string getTag() const;

    //Methods
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void createText();
    void createCountdown(float dt);
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);

    void update(float dt) override;
    void want_to_spawn();
    bool isMarkedForDeletion() const;


private:

    // Atributos
    float m_enemydeltaClock = 0;
    float m_countdowndeltaClock = 0;
    std::vector<Enemy*> m_enemyGrid;
    ObjectPooler<Enemy> m_enemyObjectPool;
    MyText* m_countdown_text;

    bool move_down = false;
    bool move_to_left = false;
    bool have_to_spawn = false;


    //Methods
    void spawn(int level);

    void deleteObjects();

    void CheckLost();


};