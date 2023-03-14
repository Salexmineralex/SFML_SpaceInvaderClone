#pragma once
#include "UIGameobject.h"
#include "TextureLoader.h"
#include "MyText.h"

class ProgressBar : public UIGameobject
{
public:

	ProgressBar();
	ProgressBar(std::string label);


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::string getTag() const;

	void setPosition(sf::Vector2f position);

	void setOrigin(sf::Vector2f position);

	int getPercentage();

	void setPercentage(int percentage);


	ProgressBar* getProgressBar();



private:

	//Atributtes
	sf::Sprite frame;
	sf::Texture* texture_frame;
	sf::Sprite progressBar;
	sf::Texture* texture_progressBar;

	MyText m_label;
	
	int actualPercentage;

	//Methods
	void ProgressBar::create_m_Label();

};


