#pragma once
#include <SFML/Graphics.hpp>

class InputManager 
{
public:
   
	InputManager(sf::RenderWindow& window);

	bool GetKeyPressed(sf::Keyboard::Key key);

private:

	sf::RenderWindow& m_window;

};