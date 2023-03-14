#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "InputManager.h"
#include "UIGameobject.h"
class UIManager
{
public:
    UIManager(sf::RenderWindow& window);


    //Methods
    void update(float dt);
    void draw();

    void addObject(UIGameobject* object);

    void deleteObjects();


private:
    sf::RenderWindow& mWindow;
    std::vector<UIGameobject*> objects;
    std::vector<UIGameobject*> pendingobjects;
    // other game objects and variables
};