#include "Hazard.h"

Hazard::Hazard(Vector2f position)
{
	m_Shape.setFillColor(Color::Red);
	m_Shape.setSize({ 100, 100 });
	m_Shape.setPosition(position);
}

RectangleShape Hazard::getShape()
{
	return m_Shape;
}