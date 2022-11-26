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
	m_Level1Buffer.loadFromFile("sound/level1.wav");
	m_Level2Buffer.loadFromFile("sound/level2.wav");
	m_Level3Buffer.loadFromFile("sound/level3.wav");
	m_Level4Buffer.loadFromFile("sound/level4.wav");
	m_Level5Buffer.loadFromFile("sound/level5.wav");
	m_Level6Buffer.loadFromFile("sound/level6.wav");
	m_Level7Buffer.loadFromFile("sound/level7.wav");
	m_Level8Buffer.loadFromFile("sound/level8.wav");

	// Associate the sounds with the buffers
	m_FallInFireSound.setBuffer(m_FallInFireBuffer);
	m_FallInPurpleSound.setBuffer(m_FallInPurpleBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);
	m_SlimeSound.setBuffer(m_SlimeBuffer);

	m_Level1.setBuffer(m_Level1Buffer);
	m_Level2.setBuffer(m_Level2Buffer);
	m_Level3.setBuffer(m_Level3Buffer);
	m_Level4.setBuffer(m_Level4Buffer);
	m_Level5.setBuffer(m_Level5Buffer);
	m_Level6.setBuffer(m_Level6Buffer);
	m_Level7.setBuffer(m_Level7Buffer);
	m_Level8.setBuffer(m_Level8Buffer);
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

void SoundManager::playNarration(int level)
{
	switch (level)
	{
	case 1:
		m_Level1.play();
		break;
	case 2:
		m_Level2.play();
		break;
	case 3:
		m_Level3.play();
		break;
	case 4:
		m_Level4.play();
		break;
	case 5:
		m_Level5.play();
		break;
	case 6:
		m_Level6.play();
		break;
	case 7:
		m_Level7.play();
		break;
	case 8:
		m_Level8.play();
		break;
	}
}

void SoundManager::stopPreviousNarration(int level)
{
	switch (level)
	{
	case 1:
		m_Level1.stop();
		break;
	case 2:
		m_Level2.stop();
		break;
	case 3:
		m_Level3.stop();
		break;
	case 4:
		m_Level4.stop();
		break;
	case 5:
		m_Level5.stop();
		break;
	case 6:
		m_Level6.stop();
		break;
	case 7:
		m_Level7.stop();
		break;
	case 8:
		m_Level8.stop();
		break;
	}
}