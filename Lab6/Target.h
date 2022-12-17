#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Target
{
private:
	RectangleShape m_Shape;
	int m_Health = 10;

public:
	Target(Vector2f position);
	RectangleShape getShape();
	int getHealth();
	FloatRect getPosition();
	void takeDamage(int damage);
};