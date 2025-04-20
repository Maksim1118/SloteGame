#pragma once
#include "MyShape.h"

class Circle :public MyShape
{
public:
	Circle();
	virtual size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(size_t index) const override;
	MyShape* clone() override;
	void setRadius(float radius);
	float getRadius() const;
private:
	static const size_t m_PointCount = 30;
	float m_Radius;
};