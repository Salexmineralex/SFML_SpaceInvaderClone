#include "GameOverWindow.h"
#include <iostream>
#include "Game.h"
GameOverWindow::GameOverWindow()
{

    title = sf::Text("Game Over", *Game::getInstance()->getFont(), 80);
    title.setFillColor(sf::Color::Green);
    title.setPosition(Game::getInstance()->getWindow()->getSize().x / 2 - title.getGlobalBounds().width / 2, 100);

    // Create score text
    score = sf::Text("Your score:" + Game::getInstance()->getScoreLifeManager()->getScore(), *Game::getInstance()->getFont(), 40);
    score.setFillColor(sf::Color::Green);
    score.setPosition(Game::getInstance()->getWindow()->getSize().x / 2 - score.getGlobalBounds().width / 2, 250);

    // Create replay button
    replayButton = sf::RectangleShape(sf::Vector2f(200, 50));
    replayButton.setPosition(Game::getInstance()->getWindow()->getSize().x / 2 - replayButton.getSize().x / 2, 400);
    replayButton.setFillColor(sf::Color::Green);

    // Create replay button text
    replayButtonText = sf::Text("Replay", *Game::getInstance()->getFont(), 40);
    replayButtonText.setFillColor(sf::Color::White);
    replayButtonText.setPosition(replayButton.getPosition().x + replayButton.getSize().x / 2 - replayButtonText.getGlobalBounds().width / 2, replayButton.getPosition().y + replayButton.getSize().y / 2 - replayButtonText.getGlobalBounds().height / 2);

    // Create quit button
    quitButton = sf::RectangleShape(sf::Vector2f(400, 50));
    quitButton.setPosition(Game::getInstance()->getWindow()->getSize().x / 2 - replayButton.getSize().x / 2, 400);
    quitButton.setFillColor(sf::Color::Green);

    // Create quit button text
    quitButtonText = sf::Text("Quit", *Game::getInstance()->getFont(), 40);
    quitButtonText.setFillColor(sf::Color::White);
    quitButtonText.setPosition(replayButton.getPosition().x + replayButton.getSize().x / 2 - replayButtonText.getGlobalBounds().width / 2, replayButton.getPosition().y + replayButton.getSize().y / 2 - replayButtonText.getGlobalBounds().height / 2);

}

void GameOverWindow::update(float dt)
{
 

    //for (auto gameobject : this->m_drawableobjects) {
    //    gameobject->update(dt);

    //}


}


void GameOverWindow::draw(sf::RenderWindow& window)
{

   window.draw(title);
   window.draw(replayButtonText);
   window.draw(quitButtonText);
   window.draw(replayButton);
   window.draw(quitButton);
   window.draw(score);

}
