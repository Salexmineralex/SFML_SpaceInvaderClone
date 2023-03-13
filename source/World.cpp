#include "world.h"
#include <iostream>
World::World(sf::RenderWindow& window) :
    mWindow(window)
{
    this->objects =  std::vector<Gameobject*>();
    this->pendingobjects =  std::vector<Gameobject*>();
    this->m_InputManager = new InputManager(window);
}

void World::update(float dt)
{
    deleteObjects();

    for (auto gameobject : this->objects) {
        gameobject->update(dt);
       
    }


    CheckCollisions();
    AddPendingObjects();

}


void World::draw()
{

    for (auto& gameobject : this->objects) {

        gameobject->draw(mWindow);
    }

}

void World::deleteObjects()
{
    auto it = objects.begin();
    while (it != objects.end()) {
        if ((*it)->isMarkedForDeletion()) {
             // Delete object from heap
            it = objects.erase(it); // Remove object from vector
        }
        else {
            ++it;
        }
    }
}

void World::CheckCollisions()
{
     for (int i = 0; i < objects.size(); i++) {
        for (int j = i + 1; j < objects.size(); j++) {
            if (objects[i]->m_sprite.getGlobalBounds().intersects(objects[j]->m_sprite.getGlobalBounds())) {
                // Handle the collision between the two game objects
                objects[i]->handleCollision(*objects[j]);
                objects[j]->handleCollision(*objects[i]);
            }
        }
    }
}

void World::AddPendingObjects()
{
    
    for (auto gameobject : this->pendingobjects) {
        objects.push_back(gameobject);

    }

    pendingobjects.clear();
}

void World::addObject(Gameobject* object)
{
    this->pendingobjects.push_back(object);
}


InputManager* World::getInputManager()
{
    return this->m_InputManager;
}

