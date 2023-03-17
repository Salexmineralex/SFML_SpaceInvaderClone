#include "EnemyBullet.h"
#include <iostream>
#include "TextureLoader.h"
#include "Player.h"
#include "Game.h"




EnemyBullet::EnemyBullet()
{

    TextureLoader t;
    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile("../Assets/Sprites/Cohetes.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }



    this->setPosition(0, 0);
    this->setOrigin(0, 0);
    /*  this->m_AnimChanger.restart();
      this->m_animationSwitch = true;*/
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);
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
    if (getPosition().y >= 1000 && !mIsMarkedForDeletion)
    {
        resetBullet();
    }
    else
    {
        move(0, (1000 * dt));

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
        Game::getInstance()->getScoreLifeManager()->substractLife(10);
    }
}
void EnemyBullet::resetBullet()
{

    this->setPosition(0, 0);
    this->setVisibility(false);
    this->mIsMarkedForDeletion = true;
    ShootingEnemy::m_EnemybulletObjectPool->add_one(this);
};
