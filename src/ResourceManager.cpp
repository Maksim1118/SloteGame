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

	m_MapFont[FontName::START] = loadFont("Fonts/pixelFont.ttf");
	m_MapFont[FontName::STOP] = loadFont("Fonts/pixelFont.ttf");

	m_isLoad = true;
}

sf::Font* ResourceManager::loadFont(const std::string& path)
{
	Font* font = new Font();
	if (!font->loadFromFile(path))
	{
		cerr << "error loading font at this path: " << path << endl;
		delete font;
		return nullptr;
	}
	return font;
}

sf::Font& ResourceManager::getFont(FontName name)
{
	return *m_MapFont.at(name);
}

ResourceManager::ResourceManager()
	:m_isLoad(false)
{

}