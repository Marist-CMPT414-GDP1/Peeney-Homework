#include "Target.h"

Target::Target(Vector2f position)
{
	m_Shape.setFillColor(Color::Green);
	m_Shape.setSize({ 50, 50 });
	m_Shape.setPosition(position);
}

RectangleShape Target::getShape()
{
	return m_Shape;
}