#include "ProgressBar.h"
#include "Game.h"
ProgressBar::ProgressBar():
    actualPercentage(100)
{
    
    TextureLoader t;

    if (t.getTexture("Frame") != nullptr)
    {
        this->texture_frame = t.getTexture("Frame");
    }
    else
    {
        this->texture_frame = new  sf::Texture();

        if (!texture_frame->loadFromFile("../Assets/Sprites/progressBarFrame.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture("Frame", texture_frame);
    }

    if (t.getTexture(getTag()) != nullptr)
    {
        this->texture_progressBar = t.getTexture(getTag());
    }
    else
    {
        this->texture_progressBar = new  sf::Texture();

        if (!texture_progressBar->loadFromFile("../Assets/Sprites/progressBarFill.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), texture_progressBar);
    }


    this->setPosition(sf::Vector2f(0, 0));
    this->setOrigin(sf::Vector2f(0, 0));
    this->frame.setPosition(0, 0);
    this->progressBar.setPosition(0, 0);
    this->frame.setOrigin(0, 0);
    this->progressBar.setOrigin(0, 0);
    this->frame.setTexture(*texture_frame);
    this->progressBar.setTexture(*texture_progressBar);
    progressBar.setScale(3, 3);
    frame.setScale(3, 3);


}

ProgressBar::ProgressBar(std::string label) : ProgressBar()
{
   
    create_m_Label();
 
    m_label.getText()->setString(label);
    m_label.setPosition(sf::Vector2f(frame.getPosition().x - m_label.getText()->getGlobalBounds().width, frame.getPosition().y));

}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->mVisibility)
    {

        target.draw(this->frame, states);
        target.draw(this->progressBar, states);
        target.draw(this->m_label, states);

    }

}

std::string ProgressBar::getTag() const
{
    return "ProgressBar";
}

void ProgressBar::setPosition(sf::Vector2f position)
{
    UIGameobject::setPosition(position);
    this->frame.setPosition(position);
    this->progressBar.setPosition(position);
    

    m_label.setPosition(sf::Vector2f(frame.getPosition().x - frame.getGlobalBounds().width, frame.getPosition().y));

}

void ProgressBar::setOrigin(sf::Vector2f position)
{
    UIGameobject::setOrigin(position);
    this->frame.setOrigin(position);
    this->progressBar.setOrigin(position);
    m_label.setOrigin(sf::Vector2f(frame.getOrigin().x - m_label.getText()->getGlobalBounds().width, frame.getOrigin().y));

}

int ProgressBar::getPercentage()
{
    return this->actualPercentage;
}

void ProgressBar::setPercentage(int percentage)
{
    this->actualPercentage = percentage;
    sf::IntRect intrect = sf::IntRect(0, 0, (actualPercentage * this->texture_progressBar->getSize().x) / 100, this->texture_progressBar->getSize().y);
    this->progressBar.setTextureRect(intrect);
}

ProgressBar* ProgressBar::getProgressBar()
{
    return this;
}

void ProgressBar::create_m_Label()
{

    m_label.getText()->setFont(*Game::getFont());

    m_label.getText()->setCharacterSize(30);

    m_label.getText()->setFillColor(sf::Color::Green);


    m_label.getText()->setStyle(sf::Text::Bold);

}


