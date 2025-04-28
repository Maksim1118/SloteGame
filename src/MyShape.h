#pragma once
#include <SFML/Graphics.hpp>
class MyShape :public sf::Shape
{
public:
	MyShape();
	virtual MyShape* clone() = 0;
	virtual sf::Vector2f getCenter()=0;
	virtual int getID();
protected:
	int m_Id;
};