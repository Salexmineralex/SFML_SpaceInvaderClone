#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "InputManager.h"
#include "UIManager.h"

class World
{
public:
    World();

    //Methods
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void deleteObjects();

    void CheckCollisions();

    void AddPendingObjects();

    void addObject(Gameobject* object);

private:

    std::vector<Gameobject*> m_drawableobjects;
    std::vector<Gameobject*> m_pendingobjects;
    // other game objects and variables
};