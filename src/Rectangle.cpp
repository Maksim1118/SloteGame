#include "Rectangle.h"

using namespace sf;

Rectangle::Rectangle()
	:m_Size(0.f, 0.f)
{
	m_Id = 3;
}

size_t Rectangle::getPointCount() const
{
	return m_PointCount;
}

sf::Vector2f Rectangle::getPoint(size_t index) const
{
	Vector2f point;
	switch (index)
	{
		case 0:
		{
			point = { 0.f, 0.f };
			break;
		}
		case 1:
		{
			point = { m_Size.x, 0.f };
			break;
		}
		case 2:
		{
			point = { m_Size.x, m_Size.y };
			break;
		}
		case 3:
		{
			point = { 0.f, m_Size.y };
		}
		default:
			break;
	}
	return point;
}

void Rectangle::setSize(Vector2f size)
{
	m_Size = size;
	update();
}

MyShape* Rectangle::clone()
{
	return new Rectangle(*this);
}

sf::Vector2f Rectangle::getCenter()
{
	return { getPosition().x + m_Size.x / 2.f, getPosition().y + m_Size.y / 2.f };
}

Vector2f Rectangle::getSize() const
{
	return m_Size;
}
