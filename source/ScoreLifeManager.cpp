#include "ScoreLifeManager.h"
#include "Game.h"
ScoreLifeManager::ScoreLifeManager():
	m_score(0),
	m_life(100)
{

	m_life_progress_bar = new ProgressBar("Life:");
	m_life_progress_bar->setPosition(sf::Vector2f(225, Game::getInstance()->getWindow()->getSize().y - 50));
	m_life_progress_bar->setPercentage(m_life);
	Game::getInstance()->getUIManager()->addObject(m_life_progress_bar);

	m_score_text = new MyText();
	createScoreText();
	m_score_text->getText()->setString("Score:" + std::to_string(m_score));
	Game::getInstance()->getUIManager()->addObject(m_score_text);


}

ScoreLifeManager::ScoreLifeManager(int score, int life) :
	m_score(score),
	m_life(life)
{

	m_life_progress_bar = new ProgressBar("Life:");
	m_life_progress_bar->setPosition(sf::Vector2f(225, Game::getInstance()->getWindow()->getSize().y - 50));
	m_life_progress_bar->setPercentage(m_life);
	Game::getInstance()->getUIManager()->addObject(m_life_progress_bar);

	m_score_text = new MyText();
	createScoreText();
	m_score_text->getText()->setString("Score:" + std::to_string(m_score));
	Game::getInstance()->getUIManager()->addObject(m_score_text);
	
}

ScoreLifeManager::~ScoreLifeManager()
{
	delete m_score_text;
	delete m_life_progress_bar;
}

void ScoreLifeManager::addLife(int heal)
{
	if(m_life+heal >= m_maxLife)
	{ 
		m_life = m_maxLife;

		m_life_progress_bar->setPercentage(m_life);
	}
	else if(m_life < m_maxLife)
	{
		m_life +=  heal;
		
		m_life_progress_bar->setPercentage(m_life);
	}
}

void ScoreLifeManager::substractLife(int damage)
{
	if (m_life - damage <= 0)
	{
		m_life = 0;

		m_life_progress_bar->setPercentage(m_life);
	}
	else if (m_life > 0 )
	{
		m_life -= damage;

		m_life_progress_bar->setPercentage(m_life);
	}
}

void ScoreLifeManager::addScore(int addScore)
{
	m_score += addScore;
	m_score_text->getText()->setString("Score:" + std::to_string(m_score));
}

void ScoreLifeManager::substractScore(int subsScore)
{
	m_score -= subsScore;
	m_score_text->getText()->setString("Score:" + std::to_string(m_score));
}

int ScoreLifeManager::getLife()
{
	return m_life;
}

int ScoreLifeManager::getScore()
{
	return m_score;
}

void ScoreLifeManager::createScoreText()
{


	m_score_text->getText()->setFont(*Game::getInstance()->getFont());

	m_score_text->getText()->setCharacterSize(100);

	m_score_text->getText()->setFillColor(sf::Color::Green);


	m_score_text->getText()->setStyle(sf::Text::Bold);
	m_score_text->getText()->setScale(0.3, 0.3);
	m_score_text->setPosition(sf::Vector2f(1300, Game::getInstance()->getWindow()->getSize().y - 50));
	m_score_text->setOrigin(sf::Vector2f(0, 0));

}