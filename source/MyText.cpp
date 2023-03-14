#include "MyText.h"

MyText::MyText()
{
    this->actualText = sf::Text();
}

void MyText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->mVisibility)
    {
      
        target.draw(this->actualText, states);
    
    }

}

std::string MyText::getTag() const
{
    return "MyText";
}

void MyText::setPosition(sf::Vector2f position)
{
    UIGameobject::setPosition(position);
    this->actualText.setPosition(position);
}

void MyText::setOrigin(sf::Vector2f position)
{
    UIGameobject::setOrigin(position);
    this->actualText.setOrigin(position);
}

sf::Text* MyText::getText()
{
    return &this->actualText;
}




