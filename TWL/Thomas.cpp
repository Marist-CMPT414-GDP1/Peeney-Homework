#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/thomas.png"));

	m_JumpDuration = .45;

	m_CharacterID = 0;
}

// A virtual function
bool Thomas::handleInput()
{
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W) && !m_Sticking)
	{

		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;

	}
	if (Keyboard::isKeyPressed(Keyboard::A)
		|| (Keyboard::isKeyPressed(Keyboard::Left) && m_Stacked))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::D)
		|| (Keyboard::isKeyPressed(Keyboard::Right) && m_Stacked))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		m_IsRespawning = true;
	}

	return m_JustJumped;
}

bool Thomas::checkVulnerability(int blockID)
{
	if (blockID == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}