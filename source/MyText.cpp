#include "MyText.h"

MyText::MyText()
{
    this->m_actualText = sf::Text();
}

void MyText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->m_Visibility)
    {
      
        target.draw(this->m_actualText, states);
    
    }

}

std::string MyText::getTag() const
{
    return "MyText";
}

void MyText::setPosition(sf::Vector2f position)
{
    UIGameobject::setPosition(position);
    this->m_actualText.setPosition(position);
}



void MyText::setOrigin(sf::Vector2f position)
{
    UIGameobject::setOrigin(position);
    this->m_actualText.setOrigin(position);
}

sf::Text* MyText::getText()
{
    return &this->m_actualText;
}




