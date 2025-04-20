#include "Circle.h"
#define PI 3.1415926535

using namespace sf;



Circle::Circle()
	:m_Radius(0.f)
{

}

size_t Circle::getPointCount() const
{
	return m_PointCount;
}

Vector2f Circle::getPoint(size_t index) const
{
	float angle = static_cast<float>(index) * 2.f * PI/ static_cast<float>(m_PointCount) - PI / 2.f;
	float x = std::cos(angle) * m_Radius;
	float y = std::sin(angle) * m_Radius;

	return Vector2f(m_Radius + x, m_Radius + y);
}

MyShape* Circle::clone()
{
	return new Circle(*this);
}

void Circle::setRadius(float radius)
{
	m_Radius = radius;
	update();
}

float Circle::getRadius() const
{
	return m_Radius;
}
