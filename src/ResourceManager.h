#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

enum class FontName
{
	START,
	STOP
};

using FontMap = std::unordered_map<FontName, sf::Font*>;

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	void load();
	sf::Font& getFont(FontName name);
private:
	sf::Font* loadFont(const std::string& path);
	ResourceManager();
	bool m_isLoad;
	FontMap m_MapFont;
};