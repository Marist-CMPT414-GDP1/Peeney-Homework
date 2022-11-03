#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Saber
{
private:
	Vector2f position;

	Vector2f initialPos;

	Sprite spriteSaber;

	float speed = 1000;

	bool poweredUp = false;

	float powerTimer = 5;

	Texture textureSaber;

	Texture texturePoweredSaber;

public:
	//Constructor
	Saber(float startX, float startY);

	//Enum class definition
	enum class movement { UP, DOWN, LEFT, RIGHT, NONE };

	//Public member variable
	movement saberMovement = { movement::NONE };

	//Function prototypes
	Sprite getSprite();

	FloatRect getDimensions();

	bool getPowerState();

	void powerUp();

	void move(movement movement);

	void update(Time dt);
};