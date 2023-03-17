#include "Enemy.h"
#include "Game.h"
#include <iostream>

Enemy::Enemy()
{
    TextureLoader t;

    if(t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile("../Assets/Sprites/enemie_sprite.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }



    this->setPosition(sf::Vector2f(0,0));
    this->setOrigin(0, 0);
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);
}

Enemy::~Enemy()
{
    delete m_texture;
}

const sf::Texture* Enemy::getTexture()
{
    return this->m_texture;
}

const sf::Sprite Enemy::getSprite()
{
    return this->m_sprite;
}
std::string Enemy::getTag() const
{
    return "Enemy";
}
;

void Enemy::setPosition(sf::Vector2f position)
{
 
    Gameobject::setPosition(position);
    m_sprite.setPosition(getPosition());
}

// Override the move function to update the sprite's position
void Enemy::move(float offsetX, float offsetY)
{

    Gameobject::setPosition(sf::Vector2f(this->getPosition().x + offsetX, this->getPosition().y + offsetY));
    m_sprite.setPosition(getPosition());
 
}

void Enemy::update(float dt)
{

    


}
bool Enemy::isMarkedForDeletion() const
{
    return Gameobject::mIsMarkedForDeletion;
}

bool Enemy::collidesWith(const Gameobject& other) const
{
    return true;
}

void Enemy::handleCollision(Gameobject& other)
{

    if(other.getTag() == "Bullet")
    {

        std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(1, 100);
        int randomNumber = uniformDistribution(rng);

        if (randomNumber <= 5)
        {
            SpecialObject* so = new SpecialObject();
            so->setPosition(getPosition().x, getPosition().y);
            Game::getInstance()->getWorld()->addObject(so);
        }

        setPosition(sf::Vector2f(0, 0));
        setVisibility(false);
        mIsMarkedForDeletion = true;
        Game::getInstance()->getScoreLifeManager()->addScore(this->m_score);

    }

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->mVisibility)
    {
        target.draw(m_sprite, states);
    }
};