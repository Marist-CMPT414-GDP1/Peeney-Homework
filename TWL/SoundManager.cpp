#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundManager::SoundManager()
{
	// Load the sound in to the buffers
	m_FallInFireBuffer.loadFromFile("sound/shock.wav");
	m_FallInPurpleBuffer.loadFromFile("sound/purple_shock.wav");
	m_JumpBuffer.loadFromFile("sound/jump.wav");
	m_ReachGoalBuffer.loadFromFile("sound/reachgoal.wav");
	m_SlimeBuffer.loadFromFile("sound/slime2.wav");

	// Associate the sounds with the buffers
	m_FallInFireSound.setBuffer(m_FallInFireBuffer);
	m_FallInPurpleSound.setBuffer(m_FallInPurpleBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);
	m_SlimeSound.setBuffer(m_SlimeBuffer);
}

void SoundManager::playFallInFire()
{
	m_FallInFireSound.setRelativeToListener(true);
	m_FallInFireSound.play();
}

void SoundManager::playFallInPurple()
{
	m_FallInPurpleSound.setRelativeToListener(true);
	m_FallInPurpleSound.play();
}

void SoundManager::playJump()
{
	m_JumpSound.setRelativeToListener(true);
	m_JumpSound.play();
}

void SoundManager::playReachGoal()
{
	m_ReachGoalSound.setRelativeToListener(true);
	m_ReachGoalSound.play();
}

void SoundManager::playSlime()
{
	m_SlimeSound.setRelativeToListener(true);
	m_SlimeSound.play();
}
