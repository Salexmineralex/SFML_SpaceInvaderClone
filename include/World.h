#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "InputManager.h"
#include "UIManager.h"

class World
{
public:
    World(sf::RenderWindow& window);


    //Methods
    void update(float dt);
    void draw();

    void deleteObjects();

    void CheckCollisions();

    void AddPendingObjects();

    void addObject(Gameobject* object);


    InputManager* getInputManager();
    UIManager* getUIManager();

private:
    sf::RenderWindow& mWindow;
    std::vector<Gameobject*> objects;
    std::vector<Gameobject*> pendingobjects;
    InputManager* m_InputManager;
   

    // other game objects and variables
};