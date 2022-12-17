#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hazard
{
private:
	RectangleShape m_Shape;
	float m_DamageOutput = 5;

public:
	Hazard(Vector2f position);
	RectangleShape getShape();
};