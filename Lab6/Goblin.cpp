#include "Goblin.h"

Goblin::Goblin() {}

void Goblin::spawn(Vector2f startPosition)
{
	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

}

// A virtual function
void Goblin::handleInput()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_UpPressed = true;
	}
	else
	{
		m_UpPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_DownPressed = true;
	}
	else
	{
		m_DownPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}
}

void Goblin::update(float elapsedTime)
{

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
		if (m_Position.x + m_Sprite.getGlobalBounds().width > 640)
		{
			stopRight(m_Position);
		}
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
		if (m_Position.x < 0)
		{
			stopLeft(m_Position);
		}
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
		if (m_Position.y + m_Sprite.getGlobalBounds().height > 640)
		{
			stopDown(m_Position);
		}
	}

	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
		if (m_Position.y < 0)
		{
			stopUp(m_Position);
		}
	}

	m_Sprite.setPosition(m_Position);

}

FloatRect Goblin::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Goblin::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

Sprite Goblin::getSprite()
{
	return m_Sprite;
}

void Goblin::stopRight(Vector2f position)
{

	m_Position.x = position.x - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Goblin::stopLeft(Vector2f position)
{
	m_Position.x = position.x + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Goblin::stopDown(Vector2f position)
{

	m_Position.y = position.y - m_Sprite.getGlobalBounds().height;
	m_Sprite.setPosition(m_Position);
}

void Goblin::stopUp(Vector2f position)
{
	m_Position.y = position.y + m_Sprite.getGlobalBounds().height;
	m_Sprite.setPosition(m_Position);
}