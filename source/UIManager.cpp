#include "world.h"
#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow& window) :
    mWindow(window)
{
    this->objects = std::vector<sf::Text*>();
    this->pendingobjects = std::vector<sf::Text*>();
}

void UIManager::update(float dt)
{
    for (auto gameobject : this->pendingobjects) {
        objects.push_back(gameobject);

    }

    pendingobjects.clear();


}


void UIManager::draw()
{

    
    for (sf::Text* gameobject : this->objects) 
    {
        mWindow.draw(*gameobject);
        
    }

    objects.clear();

}

void UIManager::addObject(sf::Text* object)
{
    this->pendingobjects.push_back(object);
}



