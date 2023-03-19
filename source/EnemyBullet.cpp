#include "EnemyBullet.h"
#include <iostream>
#include "TextureLoader.h"
#include "Player.h"
#include "Game.h"



EnemyBullet::EnemyBullet():
    m_DAMAGE(Game::getInstance()->getData()["EnemyBullet"]["damage"]),
    m_BULLET_SPEED(Game::getInstance()->getData()["EnemyBullet"]["bulletSpeed"])
{
    TextureLoader t;

    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile(Game::getInstance()->getData()["EnemyBullet"]["texturePath"]))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }


    this->setPosition(Game::getInstance()->getData()["EnemyBullet"]["position"][0], Game::getInstance()->getData()["EnemyBullet"]["position"][1]);
    this->setOrigin(Game::getInstance()->getData()["EnemyBullet"]["origin"][0], Game::getInstance()->getData()["EnemyBullet"]["origin"][1]);
    m_sprite.setPosition(sf::Vector2f(Game::getInstance()->getData()["EnemyBullet"]["position"][0], Game::getInstance()->getData()["EnemyBullet"]["position"][1]));
    m_sprite.setOrigin(Game::getInstance()->getData()["EnemyBullet"]["origin"][0], Game::getInstance()->getData()["EnemyBullet"]["origin"][1]);
    m_currentframe.width = Game::getInstance()->getData()["EnemyBullet"]["currentFrame"]["width"];
    m_currentframe.height = Game::getInstance()->getData()["EnemyBullet"]["currentFrame"]["height"];
    m_sprite.rotate(180);


}

EnemyBullet::~EnemyBullet()
{
    delete m_texture;
}



const sf::Texture* EnemyBullet::getTexture()
{
    return this->m_texture;
}

const sf::Sprite EnemyBullet::getSprite()
{
    return this->m_sprite;
}
std::string EnemyBullet::getTag() const
{
    return "EnemyBullet";
}
;


void EnemyBullet::update(float dt)
{
    if (getPosition().y >= 1000 && !m_IsMarkedForDeletion)
    {
        resetBullet();
    }
    else
    {
        move(0, (m_BULLET_SPEED * dt));

    }
}

bool EnemyBullet::collidesWith(const Gameobject& other) const
{

    if (this->m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds()))
    {
        return true;
    }

    return false;
};

void EnemyBullet::handleCollision(Gameobject& other)
{
    if (other.getTag() == "Player")
    {
        resetBullet();
        Game::getInstance()->getScoreLifeManager()->substractLife(m_DAMAGE);
    }
}
void EnemyBullet::resetBullet()
{

    this->setPosition(0, 0);
    this->setVisibility(false);
    this->m_IsMarkedForDeletion = true;
    ShootingEnemy::m_EnemybulletObjectPool->add_one(this);
};
