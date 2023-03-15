#pragma once
#include "UIGameobject.h"
#include "TextureLoader.h"
#include "MyText.h"

class ProgressBar : public UIGameobject
{
public:

	//Constructor
	ProgressBar();
	ProgressBar(std::string label);
	~ProgressBar();

	//Get&Setter
	std::string getTag() const;

	void setPosition(sf::Vector2f position);

	void setOrigin(sf::Vector2f position);

	int getPercentage();

	void setPercentage(int percentage);

	ProgressBar* getProgressBar();

	//Methods

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;



private:

	//Atributtes
	sf::Sprite m_frame;
	sf::Texture* m_texture_frame = nullptr;
	sf::Sprite m_progressBar;
	sf::Texture* m_texture_progressBar = nullptr;

	MyText m_label;
	
	int m_actualPercentage;

	//Methods
	void ProgressBar::create_m_Label();

};


