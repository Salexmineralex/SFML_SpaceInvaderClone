#include "world.h"
#include "UIManager.h"

UIManager::UIManager()
{
    this->m_drawableobjects = std::vector<UIGameobject*>();
    this->m_pendingobjects = std::vector<UIGameobject*>();
}

void UIManager::update(float dt)
{
    deleteObjects();
    for (auto gameobject : this->m_pendingobjects) {
        m_drawableobjects.push_back(gameobject);

    }

    m_pendingobjects.clear();
   

}


void UIManager::draw(sf::RenderWindow& window)
{

    
    for (UIGameobject* gameobject : this->m_drawableobjects)
    {
        window.draw(*gameobject);
        
    }


}

void UIManager::addObject(UIGameobject* object)
{
    this->m_pendingobjects.push_back(object);
}

void UIManager::deleteObjects()
{
    auto it = m_drawableobjects.begin();
    while (it != m_drawableobjects.end()) {
        if ((*it)->isMarkedForDeletion()) {
            
            it = m_drawableobjects.erase(it); // Remove object from vector
        }
        else {
            ++it;
        }
    }
}



