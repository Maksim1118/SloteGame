#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyShape.h"

class Slote
{
public:
	Slote();
	~Slote();
	void setSymbols(std::vector<MyShape*>& symbols);
	void draw(sf::RenderTarget& target) const;
private:
	void setPosition();
	int m_Id;
	std::vector<MyShape*> m_Symbols;
};