#pragma once
#include "MyShape.h"

class Triangle :public MyShape
{
public:
	Triangle();
	virtual size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(size_t index) const override;
	MyShape* clone() override;
	sf::Vector2f getCenter()override;
	void setSize(float size);
	float getSize() const;
private:
	float m_Size;
	static const size_t m_PointCount = 3;
};