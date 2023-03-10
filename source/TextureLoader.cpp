#include "TextureLoader.h"

std::unordered_map<std::string, sf::Texture*> TextureLoader::Textures;
void TextureLoader::addTexture(std::string key, sf::Texture* texture)
{

	std::pair<std::string, sf::Texture*> texture_pair(key, texture);
	Textures.insert(texture_pair);
}

sf::Texture* TextureLoader::getTexture(std::string key)
{
	try
	{
		return Textures.at(key);
	}
	catch (const std::exception&)
	{
		return nullptr;
	}

}
