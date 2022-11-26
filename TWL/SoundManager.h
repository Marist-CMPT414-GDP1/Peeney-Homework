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
	SoundBuffer m_Level1Buffer;
	SoundBuffer m_Level2Buffer;
	SoundBuffer m_Level3Buffer;
	SoundBuffer m_Level4Buffer;
	SoundBuffer m_Level5Buffer;
	SoundBuffer m_Level6Buffer;
	SoundBuffer m_Level7Buffer;
	SoundBuffer m_Level8Buffer;


	// The Sounds
	Sound m_FallInFireSound;
	Sound m_FallInPurpleSound;
	Sound m_JumpSound;
	Sound m_ReachGoalSound;
	Sound m_SlimeSound;
	Sound m_Level1;
	Sound m_Level2;
	Sound m_Level3;
	Sound m_Level4;
	Sound m_Level5;
	Sound m_Level6;
	Sound m_Level7;
	Sound m_Level8;


	// Which sound should we use next, fire 1, 2 or 3
	int m_NextSound = 1;

public:

	SoundManager();

	void playFallInFire();
	void playFallInPurple();
	void playJump();
	void playReachGoal();
	void playSlime();
	void playNarration(int level);
	void stopPreviousNarration(int level);
};

