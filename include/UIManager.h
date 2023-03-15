#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "InputManager.h"
#include "UIGameobject.h"
class UIManager
{
public:
    UIManager();


    //Methods
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void addObject(UIGameobject* object);

    void deleteObjects();


private:

    std::vector<UIGameobject*> m_drawableobjects;
    std::vector<UIGameobject*> m_pendingobjects;
    // other game objects and variables
};