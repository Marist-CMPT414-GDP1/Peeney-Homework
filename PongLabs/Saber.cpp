#include "Saber.h"

//Saber::Saber = using the Saber function (constructor) from the Saber class

Saber::Saber(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	initialPos.x = startX;
	initialPos.y = startY;

	textureSaber.loadFromFile("graphics/lightsaber.png");
	texturePoweredSaber.loadFromFile("graphics/lightsaber_powered.png");
	spriteSaber.setTexture(textureSaber);
}

Sprite Saber::getSprite()
{
	return spriteSaber;
}

FloatRect Saber::getDimensions()
{
	return spriteSaber.getGlobalBounds();
}

bool Saber::getPowerState()
{
	return poweredUp;
}

void Saber::powerUp()
{
	poweredUp = true;
}

void Saber::powerDown()
{
	poweredUp = false;
}

void Saber::move(movement movement)
{
	saberMovement = movement;
}

void Saber::update(Time dt)
{
	if (poweredUp)
	{
		spriteSaber.setTexture(texturePoweredSaber);
	}
	else
	{
		spriteSaber.setTexture(textureSaber);
	}
	
	if (saberMovement == movement::LEFT && position.x >= initialPos.x) {
		position.x -= speed * dt.asSeconds();
	}

	if (saberMovement == movement::RIGHT && position.x <= initialPos.x + spriteSaber.getGlobalBounds().width / 3) {
		position.x += speed * dt.asSeconds();
	}

	if (saberMovement == movement::UP && position.y >= 0)
	{
		position.y -= speed * dt.asSeconds();
	}

	if (saberMovement == movement::DOWN && position.y <= 1080 - spriteSaber.getGlobalBounds().height)
	{
		position.y += speed * dt.asSeconds();
	}
	
	spriteSaber.setPosition(position);
	
}