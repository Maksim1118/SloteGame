#pragma once
#include "SFML/Graphics.hpp"

class Triangle :public sf::Shape
{
public:
	Triangle();
	virtual size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(size_t index) const override;
	void setSize(sf::Vector2f size);
	sf::Vector2f getSize() const;
private:
	sf::Vector2f m_Size;
	static const size_t m_PointCount = 3;
};