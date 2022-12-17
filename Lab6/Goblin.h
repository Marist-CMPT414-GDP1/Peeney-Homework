#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Goblin
{
protected:
	Sprite m_Sprite;
	Texture m_Texture;
	Vector2f m_Position;

	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	float m_Speed;
	int m_Health;
	int m_DamageOutput;
	int m_Mitigation;

	Goblin();

public:

	void spawn(Vector2f startPosition);

	void handleInput();

	// Where is the player
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	int getHealth();
	int getDamageOutput();
	int getMitigation();

	void takeDamage(int damage);

	// Make the character stand firm
	void stopRight(Vector2f position);
	void stopLeft(Vector2f position);
	void stopDown(Vector2f position);
	void stopUp(Vector2f position);

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);
};