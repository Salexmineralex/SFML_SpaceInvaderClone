#include "ShootingEnemy.h"
#include "Player.h"
#include "EnemyBullet.h"

ObjectPooler<EnemyBullet>* ShootingEnemy::m_EnemybulletObjectPool;


ShootingEnemy::ShootingEnemy()
{
    TextureLoader t;

    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile("../Assets/Sprites/shooting_enemy_sprite.png"))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }



    this->setPosition(sf::Vector2f(0, 0));
    this->setOrigin(0, 0);
    m_sprite.setPosition(0, 0);
    m_sprite.setTexture(*this->m_texture);
    m_sprite.setOrigin(0, 0);

    this->m_EnemybulletObjectPool = new ObjectPooler<EnemyBullet>(3);

}

const sf::Texture* ShootingEnemy::getTexture()
{
	return m_texture;
}

const sf::Sprite ShootingEnemy::getSprite()
{
	return m_sprite;
}

std::string ShootingEnemy::getTag() const
{
	return "ShootingEnemy";
}

void ShootingEnemy::move(float offsetX, float offsetY)
{
   

    Enemy::move(offsetX, offsetY);

}

void ShootingEnemy::update(float dt)
{
    if(m_timeToShootdeltaClock >= (3.6609 * exp(-0.199 * Game::getInstance()->getLevel())))
    {
      
        EnemyBullet* eb = ShootingEnemy::m_EnemybulletObjectPool->get_one();

        eb->mIsMarkedForDeletion = false;

        eb->setVisibility(true);

        eb->setPosition(getPosition().x+getTexture()->getSize().x, getPosition().y - 20);

        Game::getInstance()->getWorld()->addObject(eb);

        m_timeToShootdeltaClock = 0;
    }

    m_timeToShootdeltaClock += dt;
}

bool ShootingEnemy::collidesWith(const Gameobject& other) const
{
    return true;
}

void ShootingEnemy::handleCollision(Gameobject& other)
{

    if (other.getTag() == "Bullet")
    {
        std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(1, 100);
        int randomNumber = uniformDistribution(rng);

        if (randomNumber <= 10)
        {
            SpecialObject* so = new SpecialObject();
            so->setPosition(getPosition().x, getPosition().y);
            Game::getInstance()->getWorld()->addObject(so);
        }

        setPosition(sf::Vector2f(0, 0));
        setVisibility(false);
        mIsMarkedForDeletion = true;
        Game::getInstance()->getScoreLifeManager()->addScore(m_score);

   

    }

}

