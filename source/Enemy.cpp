#include "Enemy.h"
#include "Game.h"
#include <iostream>

//    m_speed(Game::getInstance()->getData()["Player"]["speed"]),
//m_TIME_TO_RESHOOT(Game::getInstance()->getData()["Player"]["time_to_reshoot"]),
//m_POWERUP_DURATION(Game::getInstance()->getData()["Player"]["power_up_duration"]),
//m_POWERUP_SPAWN_RATE(Game::getInstance()->getData()["Player"]["power_up_spawnrate"]);
Enemy::Enemy():
    m_score(Game::getInstance()->getData()["Enemy"]["score"]),
    m_SPECIAL_OBJECT_SPAWN_RATE(Game::getInstance()->getData()["Enemy"]["special_object_spawn_rate"])
{
    TextureLoader t;

    if(t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile(Game::getInstance()->getData()["Enemy"]["texturePath"]))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }


    this->setPosition(sf::Vector2f(Game::getInstance()->getData()["Enemy"]["position"][0], Game::getInstance()->getData()["Enemy"]["position"][1]));
    this->setOrigin(Game::getInstance()->getData()["Enemy"]["origin"][0], Game::getInstance()->getData()["Enemy"]["origin"][1]);
    m_sprite.setPosition(sf::Vector2f(Game::getInstance()->getData()["Enemy"]["position"][0], Game::getInstance()->getData()["Enemy"]["position"][1]));
    m_sprite.setOrigin(Game::getInstance()->getData()["Enemy"]["origin"][0], Game::getInstance()->getData()["Enemy"]["origin"][1]);
    m_currentframe.width = Game::getInstance()->getData()["Enemy"]["currentFrame"]["width"];
    m_currentframe.height = Game::getInstance()->getData()["Enemy"]["currentFrame"]["height"];
    m_sprite.setTexture(*this->m_texture);
    m_animState = IDLE;
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
    if(m_animState == IDLE)
    {
        m_animState = IDLE_2;
    }else
    {
        m_animState = IDLE;
    }
    Gameobject::setPosition(sf::Vector2f(this->getPosition().x + offsetX, this->getPosition().y + offsetY));
    m_sprite.setPosition(getPosition());
 
}

void Enemy::update(float dt)
{

    updateAnimation();


}
bool Enemy::isMarkedForDeletion() const
{
    return Gameobject::m_IsMarkedForDeletion;
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
        rng.seed((std::chrono::system_clock::now().time_since_epoch().count()));
        int randomNumber = uniformDistribution(rng);

        if (randomNumber <= m_SPECIAL_OBJECT_SPAWN_RATE)
        {
            SpecialObject* so = new SpecialObject();
            so->setPosition(getPosition().x, getPosition().y);
            Game::getInstance()->getWorld()->addObject(so);
        }

        setPosition(sf::Vector2f(0, 0));
        setVisibility(false);
        m_IsMarkedForDeletion = true;
        m_animState = IDLE;
        Game::getInstance()->getScoreLifeManager()->addScore(this->m_score);

    }

}

void Enemy::updateAnimation()
{
    if (m_animState == IDLE)
    {
        m_currentframe.top = 0;
        m_currentframe.left = 0;
        m_sprite.setTextureRect(m_currentframe);
    }
    if (m_animState == IDLE_2)
    {
        m_currentframe.top = 0;
        m_currentframe.left = 50;
        m_sprite.setTextureRect(m_currentframe);
    }
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->m_Visibility)
    {
        target.draw(m_sprite, states);
    }
};