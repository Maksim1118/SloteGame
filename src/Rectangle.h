#pragma once
#include "MyShape.h"

class Rectangle :public MyShape
{
public:
	Rectangle();
	virtual size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(size_t index) const override;
	MyShape* clone() override;
	sf::Vector2f getCenter() override;
	void setSize(sf::Vector2f size);
	sf::Vector2f getSize() const;
private:
	static const size_t m_PointCount = 4;
	sf::Vector2f m_Size;
};