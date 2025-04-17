#include "Triangle.h"

using namespace sf;

Triangle::Triangle()
	:m_Size(0.f, 0.f)
{

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
			point = { m_Size.x * 0.5f, 0.f};
			break;
		}
		case 1:
		{
			point = {0.f , m_Size.y };
			break;
		}
		case 2:
		{
			point = { m_Size.x  , m_Size.y };
			break;
		}
		default:
			break;
	}
	return point;
}

void Triangle::setSize(Vector2f size)
{
	m_Size = size;
	update();
}

Vector2f Triangle::getSize() const
{
	return m_Size;
}