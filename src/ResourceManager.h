#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	void load();
	sf::Font& getFont();
private:
	void loadFont(const std::string& path);
	ResourceManager();
	bool m_isLoad;
	sf::Font* m_Font;
};