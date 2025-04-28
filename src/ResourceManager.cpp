#include "ResourceManager.h"

using namespace sf;
using namespace std;

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager resManager;
	return resManager;
}

void ResourceManager::load()
{
	if (m_isLoad)
	{
		cerr << "Resources have been loaded\n";
	}

	loadFont("Fonts/pixelFont.ttf");

	m_isLoad = true;
}

void ResourceManager::loadFont(const std::string& path)
{
	m_Font = new Font();
	if (!m_Font->loadFromFile(path))
	{
		cerr << "error loading font at this path: " << path << endl;
		delete m_Font;
		m_Font = nullptr;
	}
}

sf::Font& ResourceManager::getFont()
{
	return *m_Font;
}

ResourceManager::ResourceManager()
	:m_isLoad(false)
{

}