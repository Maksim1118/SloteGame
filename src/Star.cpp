#include "Star.h"
#define PI 3.1415926535

using namespace sf;

Star::Star()
	:m_InnerSize(0.f), m_OuterSize(0.f)
{
	m_Id = 1;
}

size_t Star::getPointCount() const
{
	return m_PointCount * 2;
}

Vector2f  Star::getPoint(size_t index) const
{
	float angle = index * (PI / (float)m_PointCount);
	float radius = (index % 2 == 0) ? m_OuterSize/2.f : m_InnerSize/2.f;
	return Vector2f(m_OuterSize/2 + radius * cos(angle * 2.f - PI/2.f), m_OuterSize/2 + radius * sin(angle * 2.f - PI / 2.f));
}

MyShape* Star::clone()
{
	return new Star(*this);
}

sf::Vector2f Star::getCenter()
{
	return { getPosition().x + m_OuterSize / 2.f, getPosition().y + m_OuterSize / 2.f };
}

void  Star::setSize(float innerSize, float outerSize)
{
	m_InnerSize = innerSize;
	m_OuterSize = outerSize;
	update();
}

float Star::getSize() const
{
	return m_OuterSize;
}
