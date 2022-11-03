#include "Laser.h"
#include <iostream>

//Constructor
Laser::Laser(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	textureLaser.loadFromFile("graphics/laser.png");
	spriteLaser.setTexture(textureLaser);
	//spriteLaser.setPosition(position);
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

void Laser::resetLaser(float startX, float startY)
{
	position.x = startX;
	position.y = startY;
	speed = 2000.0f;
	spriteLaser.setPosition(position);
	std::cerr << "resetLaser() - respawned laser" << std::endl;
}

void Laser::update(Time dt, bool saberPowered)
{
	position.x += directionX * speed * dt.asSeconds();
	position.y += directionY * speed * dt.asSeconds();
	speed = speed - speed * 0.000015 * dt.asSeconds();
	if (increaseSpeed)
	{
		if (saberPowered) 
		{
			speed = speed * 1.3;
		}
		else
		{
			speed = speed * 1.1;
		}
		increaseSpeed = false;
	}
	if (speed < 0.5)
	{
		resetLaser(1720, 1080 / 2);
	}

	spriteLaser.setPosition(position);
}