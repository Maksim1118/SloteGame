#pragma once
#include "MyShape.h"

class Star :public MyShape
{
public:
	Star();
	virtual size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(size_t index) const override;
	MyShape* clone() override;
	sf::Vector2f getCenter() override;
	void setSize(float innerSize, float outerSize);
	float getSize() const;
private:
	static const size_t m_PointCount = 5;
	float m_InnerSize;
	float m_OuterSize;
};