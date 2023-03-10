#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "InputManager.h"

class UIManager
{
public:
    UIManager(sf::RenderWindow& window);


    //Methods
    void update(float dt);
    void draw();

    void addObject(sf::Text* object);


private:
    sf::RenderWindow& mWindow;
    std::vector<sf::Text*> objects;
    std::vector<sf::Text*> pendingobjects;
    // other game objects and variables
};