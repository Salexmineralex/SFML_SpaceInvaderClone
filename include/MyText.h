#pragma once
#include "UIGameobject.h"
#include <SFML/Graphics.hpp>

class MyText :  public UIGameobject
{
public:

	MyText();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::string getTag() const;

	void setPosition(sf::Vector2f position);

	void setOrigin(sf::Vector2f position);

	sf::Text* getText();

	
private:

	sf::Text actualText;

};


