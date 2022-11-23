#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
private:
	// The buffers
	SoundBuffer m_FallInFireBuffer;
	SoundBuffer m_FallInPurpleBuffer;
	SoundBuffer m_JumpBuffer;
	SoundBuffer m_ReachGoalBuffer;
	SoundBuffer m_SlimeBuffer;

	// The Sounds
	Sound m_FallInFireSound;
	Sound m_FallInPurpleSound;
	Sound m_JumpSound;
	Sound m_ReachGoalSound;
	Sound m_SlimeSound;

	// Which sound should we use next, fire 1, 2 or 3
	int m_NextSound = 1;

public:

	SoundManager();

	void playFallInFire();
	void playFallInPurple();
	void playJump();
	void playReachGoal();
	void playSlime();
};

