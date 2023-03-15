#include "ProgressBar.h"
#include "Game.h"
ProgressBar::ProgressBar():
    m_actualPercentage(100)
{
    
    TextureLoader t;

    if (t.getTexture("Frame") != nullptr)
    {
        this->m_texture_frame = t.getTexture("Frame");
    }
    else
    {
        this->m_texture_frame = new  sf::Texture();

        if (!m_texture_frame->loadFromFile("../Assets/Sprites/progressBarFrame.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture("Frame", m_texture_frame);
    }

    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture_progressBar = t.getTexture(getTag());
    }
    else
    {
        this->m_texture_progressBar = new  sf::Texture();

        if (!m_texture_progressBar->loadFromFile("../Assets/Sprites/progressBarFill.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture_progressBar);
    }


    this->setPosition(sf::Vector2f(0, 0));
    this->setOrigin(sf::Vector2f(0, 0));
    this->m_frame.setPosition(0, 0);
    this->m_progressBar.setPosition(0, 0);
    this->m_frame.setOrigin(0, 0);
    this->m_progressBar.setOrigin(0, 0);
    this->m_frame.setTexture(*m_texture_frame);
    this->m_progressBar.setTexture(*m_texture_progressBar);
    m_progressBar.setScale(3, 3);
    m_frame.setScale(3, 3);


}

ProgressBar::ProgressBar(std::string label) : ProgressBar()
{
   
    create_m_Label();
 
    m_label.getText()->setString(label);
    m_label.setPosition(sf::Vector2f(m_frame.getPosition().x - m_label.getText()->getGlobalBounds().width, m_frame.getPosition().y));

}

ProgressBar::~ProgressBar()
{
    delete m_texture_frame;
    delete m_texture_progressBar;
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->mVisibility)
    {

        target.draw(this->m_frame, states);
        target.draw(this->m_progressBar, states);
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
    this->m_frame.setPosition(position);
    this->m_progressBar.setPosition(position);
    

    m_label.setPosition(sf::Vector2f(m_frame.getPosition().x - m_frame.getGlobalBounds().width, m_frame.getPosition().y));

}

void ProgressBar::setOrigin(sf::Vector2f position)
{
    UIGameobject::setOrigin(position);
    this->m_frame.setOrigin(position);
    this->m_progressBar.setOrigin(position);
    m_label.setOrigin(sf::Vector2f(m_frame.getOrigin().x - m_label.getText()->getGlobalBounds().width, m_frame.getOrigin().y));

}

int ProgressBar::getPercentage()
{
    return this->m_actualPercentage;
}

void ProgressBar::setPercentage(int percentage)
{
    this->m_actualPercentage = percentage;
    sf::IntRect intrect = sf::IntRect(0, 0, (m_actualPercentage * this->m_texture_progressBar->getSize().x) / 100, this->m_texture_progressBar->getSize().y);
    this->m_progressBar.setTextureRect(intrect);
}

ProgressBar* ProgressBar::getProgressBar()
{
    return this;
}

void ProgressBar::create_m_Label()
{

    m_label.getText()->setFont(*Game::getInstance()->getFont());

    m_label.getText()->setCharacterSize(30);

    m_label.getText()->setFillColor(sf::Color::Green);


    m_label.getText()->setStyle(sf::Text::Bold);

}


