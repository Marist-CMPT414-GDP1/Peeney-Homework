#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;


void Zombie::spawn(float startX, float startY, int type, int seed)
{
	m_Type = type;
	switch (m_Type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

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
			"graphics/crawler.png"));

		m_DefaultSpeed = 20;
		m_Health = 3;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
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

bool Zombie::hit()
{
	m_Health--;

	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime,
	Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	//Change zombie behavior according to type
	
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

	// Update the zombie position variables
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
	m_directionFacingStream << "graphics/" << m_Type;

	//Determine which way the sprite should face
	if (angle > -45 && angle <= 45)
	{
		m_directionFacingStream << "_r.png";
	}
	else if (angle > 45 && angle <= 135)
	{
		m_directionFacingStream << "_d.png";
	}
	else if (angle < -45 && angle >= -135)
	{
		m_directionFacingStream << "_u.png";
	}
	else
	{
		m_directionFacingStream << "_l.png";
	}

	if (m_Type == 1)
	{
		m_Sprite.setTexture(TextureHolder::GetTexture(
			m_directionFacingStream.str()));
	}


}