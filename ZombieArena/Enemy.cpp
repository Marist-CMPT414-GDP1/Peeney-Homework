#include "Enemy.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;


void Enemy::spawn(float startX, float startY, int type, int seed)
{
	m_Type = type;
	switch (m_Type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/0_r.png"));

		m_DefaultSpeed = 40;
		m_Health = 5;
		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/1_d.png"));

		m_DefaultSpeed = 70;
		m_Health = 1;
		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/2_r.png"));

		m_DefaultSpeed = 20;
		m_Health = 3;
		break;
	}

	// Modify the speed to make the enemy unique
	// Every enemy is unique. Create a speed modifier
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_DefaultSpeed *= modifier;
	m_Speed = m_DefaultSpeed;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Enemy::hit()
{
	m_Health--;

	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/skull.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

bool Enemy::isAlive()
{
	return m_Alive;
}

FloatRect Enemy::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


Sprite Enemy::getSprite()
{
	return m_Sprite;
}

std::string Enemy::getDirection(float angle)
{
	//Determine which way the sprite should face
	if (m_Type == 1)
	{
		if (angle > -45 && angle <= 45)
		{
			return "_r.png";
		}
		else if (angle > 45 && angle <= 135)
		{
			return "_d.png";
		}
		else if (angle < -45 && angle >= -135)
		{
			return "_u.png";
		}
		else
		{
			return "_l.png";
		}
	}
	else
	{
		if (angle > -90 && angle <= 90)
		{
			return "_r.png";
		}
		else
		{
			return "_l.png";
		}
	}
}

void Enemy::update(float elapsedTime,
	Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	//Change enemy behavior according to type
	
	//Bloaters have a 1/6000 chance every frame to freeze for a bit
	if (m_Type == 0)
	{
		if (m_bloaterFreezeTime == 0)
		{
			if (m_Speed <= 0)
			{
				m_Speed = m_DefaultSpeed;
			}
			int r = (rand() % 6000);
			if (r == 0)
			{
				m_bloaterFreezeTime = rand() % 600 + 420;
			}
		}
		else
		{
			if (m_Speed == m_DefaultSpeed)
			{
				m_Speed = 0;
			}
			m_bloaterFreezeTime -= 1;
		}
	}

	//Crawlers has a 1/9000 chance of dashing forward every frame	
	if (m_Type == 2)
	{
		if (m_crawlerBoosting)
		{
			if (m_Speed < 140)
			{
				m_Speed += 10;
			}
			else
			{
				m_crawlerBoosting = false;
			}
		}
		else
		{
			if (m_Speed == m_DefaultSpeed)
			{
				int r = (rand() % 9000);
				if (r == 0)
				{
					m_crawlerBoosting = true;
				}
			}
			else if (m_Speed < m_DefaultSpeed)
			{
				m_Speed = m_DefaultSpeed;
			}
			else
			{
				m_Speed -= 0.2;
			}
		}
	}

	// Update the enemy position variables
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;

	//Reset the stream for the filename
	m_directionFacingStream.str("");
	m_directionFacingStream.clear();
	m_directionFacingStream << "graphics/" << m_Type << getDirection(angle);

	m_Sprite.setTexture(TextureHolder::GetTexture(
		m_directionFacingStream.str()));


}