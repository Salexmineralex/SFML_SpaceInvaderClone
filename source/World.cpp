#include "world.h"
#include <iostream>
World::World()
{
    this->m_drawableobjects =  std::vector<Gameobject*>();
    this->m_pendingobjects =  std::vector<Gameobject*>();
 
}

void World::update(float dt)
{
    deleteObjects();

    for (auto gameobject : this->m_drawableobjects) {
        gameobject->update(dt);
       
    }


    CheckCollisions();
    AddPendingObjects();

}


void World::draw(sf::RenderWindow& window)
{

    for (auto& gameobject : this->m_drawableobjects) {

        gameobject->draw(window);
    }

}

void World::deleteObjects()
{
    auto it = m_drawableobjects.begin();
    while (it != m_drawableobjects.end()) {
        if ((*it)->isMarkedForDeletion()) {
             // Delete object from heap
            it = m_drawableobjects.erase(it); // Remove object from vector
        }
        else {
            ++it;
        }
    }
}

void World::CheckCollisions()
{
     for (int i = 0; i < m_drawableobjects.size(); i++) {
        for (int j = i + 1; j < m_drawableobjects.size(); j++) {
            if (m_drawableobjects[i]->m_sprite.getGlobalBounds().intersects(m_drawableobjects[j]->m_sprite.getGlobalBounds())) {
                // Handle the collision between the two game objects
                m_drawableobjects[i]->handleCollision(*m_drawableobjects[j]);
                m_drawableobjects[j]->handleCollision(*m_drawableobjects[i]);
            }
        }
    }
}

void World::AddPendingObjects()
{
    
    for (auto gameobject : this->m_pendingobjects) {
        m_drawableobjects.push_back(gameobject);

    }

    m_pendingobjects.clear();
}

void World::addObject(Gameobject* object)
{
    this->m_pendingobjects.push_back(object);
}


