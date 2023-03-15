#include "TextureLoader.h"

std::unordered_map<std::string, sf::Texture*> TextureLoader::m_Textures;
void TextureLoader::addTexture(std::string key, sf::Texture* texture)
{

	std::pair<std::string, sf::Texture*> texture_pair(key, texture);
	m_Textures.insert(texture_pair);
}

sf::Texture* TextureLoader::getTexture(std::string key)
{
	try
	{
		return m_Textures.at(key);
	}
	catch (const std::exception&)
	{
		return nullptr;
	}

}
