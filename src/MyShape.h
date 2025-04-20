#pragma once
#include <SFML/Graphics.hpp>
class MyShape :public sf::Shape
{
public:
	MyShape();
	virtual MyShape* clone() = 0;
};