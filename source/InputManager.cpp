#include "InputManager.h"

InputManager::InputManager()
{
}

bool InputManager::GetKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}
