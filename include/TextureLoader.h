#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class TextureLoader
{
public:
  

    static void addTexture(std::string key, sf::Texture* texture);

    static sf::Texture* getTexture(std::string key);

private:

    static std::unordered_map<std::string, sf::Texture*> Textures;
};