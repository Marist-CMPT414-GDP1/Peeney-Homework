#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hazard
{
private:
	RectangleShape m_Shape;
	int m_DamageOutput = 2;

public:
	Hazard(Vector2f position);
	RectangleShape getShape();
	int getDamageOutput();
	FloatRect getPosition();
};