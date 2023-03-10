#include <SFML/Graphics.hpp>

#include "game.h"
#include <iostream>

//std::vector<sf::Drawable*> objects;
//
//std::vector<Bullet> bullets;
//std::vector<Enemies> enemies;
//
//
//sf::Clock deltaClock;
//
//sf::Text* CountdownText;
//
//
//bool isSpacePressed = false;
//
//int actual_level = 1;
//
//Player p;
//
//sf::Text* Create_Text(sf::RenderWindow& window)
//{
//    sf::Text* text = new sf::Text();
//
//    sf::Font* font = new sf::Font();
//    if (!font->loadFromFile("../Assets/Fonts/dogica.ttf"))
//    {
//        // error...
//    }
//
//    text->setFont(*font);
//
//    text->setCharacterSize(100);
//
//    text->setFillColor(sf::Color::Green);
//
//
//    text->setStyle(sf::Text::Bold);
//
//
//    text->setOrigin(text->getCharacterSize() / 2, text->getCharacterSize() / 2);
//    text->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
//
//    return text;
//
//}
//
//void SpawnEnemies(int level)
//{
//
//    int line = 10;
//    int colum = 0;
//
//
//    //Spawn Enemies
//    for (size_t i = 0; i < 3*level; i++)
//    {
//        Enemies p = Enemies();
//
//        p.setPosition(370 - p.getTexture()->getSize().x * colum * 2.5, line);
//        enemies.push_back(p);
//
//        Enemies g = Enemies();
//        g.setPosition(400 + p.getTexture()->getSize().x * colum * 2.5, line);
//        enemies.push_back(g);
//
//        colum++;
//
//        if (p.getPosition().x <= 150)
//        {
//            /*    Enemies p = Enemies();
//                p.setPosition(400 - (p.getTexture()->getSize().x * 2.5 * colum + 1), line);
//                enemies.push_back(p);*/
//
//            line += p.getTexture()->getSize().y*2;
//            colum = 0;
//        }
//
//    }
//}
//
//void Spawn()
//{
//    //Spawn Player
//    //p.setPosition(400, 560);
//    objects.push_back(&p);
//
//    SpawnEnemies(1);
//
//}
//
//void Draw(sf::RenderWindow& window)
//{
//    window.clear();
//
//    for (int i = 0; i < enemies.size(); i++)
//    {
//        window.draw(enemies[i]);
//    }
//    for (int i = 0; i < bullets.size(); i++)
//    {
//        window.draw(bullets[i]);
//    }
//
//
//    for (const auto& obj : objects) {
//        window.draw(*obj);
//    }
//
//    if (CountdownText != nullptr)
//    {
//        window.draw(*CountdownText);
//    }
//
//    window.display();
//
//
//}
//
//void ShootAndMove()
//{
//
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && p.getPosition().x > 0)
//    {
//
//        p.move(sf::Vector2f(-p.getSpeed() * deltaClock.getElapsedTime().asSeconds(), 0.0f));
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && p.getPosition().x < 760)
//    {
//        p.move(sf::Vector2f(p.getSpeed() * deltaClock.getElapsedTime().asSeconds(), 0.0f));
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressed)
//    {
//
//
//        p.setShooting(true);
//
//        Bullet b;
//
//        b.setPosition(p.getPosition().x, p.getPosition().y);
//
//
//        bullets.push_back(b);
//
//        isSpacePressed = true;
//
//
//    }
//
//    for (int i = 0; i < bullets.size(); i++)
//    {
//        if (bullets[i].getPosition().y < -10)
//        {
//
//            bullets.erase(bullets.begin() + i);
//        }
//        else
//        {
//            bullets[i].setPosition(bullets[i].getPosition().x, bullets[i].getPosition().y - 0.5 * actual_level); // Move the bullet up by 10 pixels
//        }
//
//    }
//}




int main()
{

    Game game;
    game.init();

    while (game.wantsToQuitGame() == false)
    {
        game.run();
    }

    //bool move_to_left = false;
    //bool move_down = false;

    //bool StartCountdown = true;

    //sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

   
    //sf::Clock SpacedeltaClock;
    //sf::Clock respawndeltaClock;
    //sf::Clock enemydeltaClock;

    //CountdownText = Create_Text(window);

    //Spawn();

    //// run the program as long as the window is open
    //while (window.isOpen())
    //{
    // 
    //    // check all the window's events that were triggered since the last iteration of the loop
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //        {
    //            window.close();
    //        }
    //        
    //       
    //    }

    //    ShootAndMove();
    //  
    // 
    //    //MOVE ENEMIES
    //    if (enemydeltaClock.getElapsedTime().asSeconds() >= 3)
    //    {
    //        if (move_down)
    //        {
    //            for (int i = 0; i < enemies.size(); i++)
    //            {
    //                enemies[i].move(0, 35);

    //            }
    //            move_down = false;

    //        }
    //        else if (!move_to_left)
    //        {

    //            for (int i = 0; i < enemies.size(); i++)
    //            {


    //                enemies[i].move(35, 0);

    //                if (enemies[i].getPosition().x > 750)
    //                {
    //                    move_to_left = true;
    //                    move_down = true;
    //                }
    //            }

    //        }
    //        else
    //        {

    //            for (int i = 0; i < enemies.size(); i++)
    //            {


    //                enemies[i].move(-35, 0);

    //                if (enemies[i].getPosition().x < 20)
    //                {
    //                    move_to_left = false;
    //                    move_down = true;
    //                }
    //            }

    //        }

    //        enemydeltaClock.restart();
    //    }
    //   

    //    //CheckIfBulletsTouchEnemies

    //    for (size_t i = 0; i < enemies.size(); i++)
    //    {
    //        for (size_t j = 0; j < bullets.size(); j++)
    //        {


    //            if (bullets[j].getSprite().getGlobalBounds().intersects(enemies[i].getSprite().getGlobalBounds()))
    //            {
    //                enemies.erase(enemies.begin() + i);
    //                bullets.erase(bullets.begin() + j);
    //            }

    //        }

    //    }

    //    if(SpacedeltaClock.getElapsedTime().asSeconds() > 1.5 && isSpacePressed)
    //    {
    //        isSpacePressed = false;
    //        SpacedeltaClock.restart();
    //    }

    //    if(enemies.size() <= 0 && StartCountdown)
    //    {

    //        respawndeltaClock.restart();
    //        StartCountdown = false;

    //    }

    //    if(!StartCountdown && respawndeltaClock.getElapsedTime().asSeconds() >= 3)
    //    {
    //        
    //        actual_level++;
    //        SpawnEnemies(actual_level);
    //        StartCountdown = true;
    //        CountdownText->setString("");

    //    }else if(!StartCountdown)
    //    {
    //        int seconds = (static_cast<int>(respawndeltaClock.getElapsedTime().asSeconds()));
    //     
    //        CountdownText->setString(std::to_string(seconds+1));
    //    }

    //    
    //    //Draw
    //    Draw(window);

    //    deltaClock.restart();
    //}

    return 0;
}




