#include "ShootingEnemy.h"
#include "Player.h"
#include "EnemyBullet.h"

ObjectPooler<EnemyBullet>* ShootingEnemy::m_EnemybulletObjectPool;


ShootingEnemy::ShootingEnemy() :
    m_score(Game::getInstance()->getData()["ShootingEnemy"]["score"]),
    m_SPECIAL_OBJECT_SPAWN_RATE(Game::getInstance()->getData()["ShootingEnemy"]["special_object_spawn_rate"])
{
    TextureLoader t;

    if (t.getTexture(getTag()) != nullptr)
    {
        this->m_texture = t.getTexture(getTag());
    }
    else
    {
        this->m_texture = new sf::Texture();

        if (!m_texture->loadFromFile(Game::getInstance()->getData()["ShootingEnemy"]["texturePath"]))
        {
            // Error loading texture

            return;
        }

        t.addTexture(getTag(), m_texture);
    }


    this->setPosition(sf::Vector2f(Game::getInstance()->getData()["ShootingEnemy"]["position"][0], Game::getInstance()->getData()["ShootingEnemy"]["position"][1]));
    this->setOrigin(Game::getInstance()->getData()["ShootingEnemy"]["origin"][0], Game::getInstance()->getData()["ShootingEnemy"]["origin"][1]);
    m_sprite.setPosition(sf::Vector2f(Game::getInstance()->getData()["ShootingEnemy"]["position"][0], Game::getInstance()->getData()["ShootingEnemy"]["position"][1]));
    m_sprite.setOrigin(Game::getInstance()->getData()["ShootingEnemy"]["origin"][0], Game::getInstance()->getData()["ShootingEnemy"]["origin"][1]);
    m_currentframe.width = Game::getInstance()->getData()["ShootingEnemy"]["currentFrame"]["width"];
    m_currentframe.height = Game::getInstance()->getData()["ShootingEnemy"]["currentFrame"]["height"];
    m_sprite.setTexture(*this->m_texture);
    m_animState = IDLE;

    this->m_EnemybulletObjectPool = new ObjectPooler<EnemyBullet>(Game::getInstance()->getData()["ShootingEnemy"]["bulletObjectPoolSize"]);

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

        eb->m_IsMarkedForDeletion = false;

        eb->setVisibility(true);

        eb->setPosition(getPosition().x +m_currentframe.width, getPosition().y - 20);

        Game::getInstance()->getWorld()->addObject(eb);

        m_timeToShootdeltaClock = 0;
    }

    m_timeToShootdeltaClock += dt;

    updateAnimation();
}

void ShootingEnemy::updateAnimation()
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

bool ShootingEnemy::collidesWith(const Gameobject& other) const
{
    return true;
}

void ShootingEnemy::handleCollision(Gameobject& other)
{

    if (other.getTag() == "Bullet")
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
        Game::getInstance()->getScoreLifeManager()->addScore(m_score);

   

    }

}

