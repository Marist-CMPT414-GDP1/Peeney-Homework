#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Laser
{
private:
	Vector2f position;

	Sprite spriteLaser;

	Texture textureLaser;

	float speed = 2000.0f;
	float directionX = -.2f;
	float directionY = -.2f;

	bool increaseSpeed = false;

public:
	Laser(float startX, float startY);

	FloatRect getPosition();

	Sprite getSprite();

	float getXVelocity();

	void reboundEdges();

	void reboundSaber();

	void reboundRight();

	void reboundLeft();

	void update(Time dt);

};
