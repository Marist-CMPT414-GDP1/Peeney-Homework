#include "Laser.h"
#include <iostream>

//Constructor
Laser::Laser(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	shape.setSize(sf::Vector2f(50, 50));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
}

FloatRect Laser::getPosition()
{
	return shape.getGlobalBounds();
}

RectangleShape Laser::getShape()
{
	return shape;
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
	position.x = 1820;
	position.y = 1080 / 2;
	speed = 2000.0f;
	std::cerr << "reboundLeft() - respawned laser" << std::endl;
}

void Laser::update(Time dt)
{
	position.x += directionX * speed * dt.asSeconds();
	position.y += directionY * speed * dt.asSeconds();
	speed = speed - speed * 0.00025;
	if (increaseSpeed)
	{
		speed = speed * 2;
		increaseSpeed = false;
	}

	shape.setPosition(position);
}