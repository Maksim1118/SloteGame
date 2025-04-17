#pragma once
#include "SFML/Graphics.hpp"

class Star :public sf::Shape
{
public:
	Star();
	virtual size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(size_t index) const override;
	void setSize(float innerSize, float outerSize);
	float getSize() const;
private:
	static const size_t m_PointCount = 5;
	float m_InnerSize;
	float m_OuterSize;
};