#pragma once
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "InputManager.h"
#include "UIManager.h"

class GameOverWindow
{
public:
    GameOverWindow();

    //Methods
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:

    sf::Text title;
    sf::Text score;
    sf::Text replayButtonText;
    sf::Text quitButtonText;
    sf::RectangleShape replayButton;
    sf::RectangleShape quitButton;

};