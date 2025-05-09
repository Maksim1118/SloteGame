#include "Triangle.h"

using namespace sf;

Triangle::Triangle()
	:m_Size(0.f)
{
	m_Id = 2;
}

size_t Triangle::getPointCount() const
{
	return m_PointCount;
}

Vector2f Triangle::getPoint(size_t index) const
{
	Vector2f point;
	switch (index)
	{
		case 0:
		{
			point = { m_Size * 0.5f, 0.f};
			break;
		}
		case 1:
		{
			point = {0.f , m_Size};
			break;
		}
		case 2:
		{
			point = { m_Size  , m_Size};
			break;
		}
		default:
			break;
	}
	return point;
}

MyShape* Triangle::clone()
{
	return new Triangle(*this);
}

sf::Vector2f Triangle::getCenter()
{
	return { getPosition().x + m_Size / 2.f, getPosition().y + m_Size / 2.f };
}

void Triangle::setSize(float size)
{
	m_Size = size;
	update();
}

float Triangle::getSize() const
{
	return m_Size;
}