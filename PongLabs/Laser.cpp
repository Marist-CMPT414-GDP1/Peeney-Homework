#include "Laser.h"
#include <iostream>

//Constructor
Laser::Laser(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	textureLaser.loadFromFile("graphics/laser.png");
	spriteLaser.setTexture(textureLaser);
}

FloatRect Laser::getPosition()
{
	return spriteLaser.getGlobalBounds();
}

Sprite Laser::getSprite()
{
	return spriteLaser;
}

float Laser::getXVelocity()
{
	return directionX;
}

void Laser::reboundEdges()
{
	directionY = -directionY;
	std::cerr << "reboundEdges()" << std::endl;
}

void Laser::reboundSaber()
{
	directionX = -directionX;
	increaseSpeed = true;
	std::cerr << "reboundSaber()" << std::endl;
}

void Laser::reboundRight()
{
	directionX = -directionX;
	std::cerr << "reboundRight()" << std::endl;
}

void Laser::reboundLeft()
{
	position.x = 1720;
	position.y = 1080 / 2;
	speed = 2000.0f;
	std::cerr << "reboundLeft() - respawned laser" << std::endl;
}

void Laser::update(Time dt)
{
	position.x += directionX * speed * dt.asSeconds();
	position.y += directionY * speed * dt.asSeconds();
	speed = speed - speed * 0.000015 * dt.asSeconds();
	if (increaseSpeed)
	{
		speed = speed * 1.1;
		increaseSpeed = false;
	}
	if (speed < 0.5)
	{
		reboundLeft();
	}

	spriteLaser.setPosition(position);
}