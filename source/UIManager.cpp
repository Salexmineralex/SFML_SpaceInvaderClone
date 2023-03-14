#include "world.h"
#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow& window) :
    mWindow(window)
{
    this->objects = std::vector<UIGameobject*>();
    this->pendingobjects = std::vector<UIGameobject*>();
}

void UIManager::update(float dt)
{
    deleteObjects();
    for (auto gameobject : this->pendingobjects) {
        objects.push_back(gameobject);

    }

    pendingobjects.clear();
   

}


void UIManager::draw()
{

    
    for (UIGameobject* gameobject : this->objects)
    {
        mWindow.draw(*gameobject);
        
    }


}

void UIManager::addObject(UIGameobject* object)
{
    this->pendingobjects.push_back(object);
}

void UIManager::deleteObjects()
{
    auto it = objects.begin();
    while (it != objects.end()) {
        if ((*it)->isMarkedForDeletion()) {
            
            it = objects.erase(it); // Remove object from vector
        }
        else {
            ++it;
        }
    }
}



