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

FloatRect Target::getPosition()
{
	return m_Shape.getGlobalBounds();
}

int Target::getHealth()
{
	return m_Health;
}

void Target::takeDamage(int damage)
{
	m_Health -= damage;
}