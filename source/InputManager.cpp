#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow& window):
	m_window(window)
{
}

bool InputManager::GetKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}
