#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/bob.png"));

	m_JumpDuration = .25;

	m_CharacterID = 1;
}

bool Bob::handleInput()
{
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::Up) && !m_Sticking)
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
	if (Keyboard::isKeyPressed(Keyboard::Left)
		|| (Keyboard::isKeyPressed(Keyboard::A) && m_Stacked))
	{
		m_LeftPressed = true;

	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::Right)
		|| (Keyboard::isKeyPressed(Keyboard::D) && m_Stacked))
	{

		m_RightPressed = true;;

	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}

bool Bob::checkVulnerability(int blockID)
{
	if (blockID == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}