#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

class Enemy
{
private:
	// How fast is each zombie type?
	const float BOWSER_SPEED = 40;
	const float GOOMBA_SPEED = 80;
	const float FISH_SPEED = 20;

	// How tough is each zombie type
	const float BOWSER_HEALTH = 5;
	const float GOOMBA_HEALTH = 1;
	const float FISH_HEALTH = 3;

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// Where is this zombie?
	Vector2f m_Position;

	// A sprite for the zombie
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_DefaultSpeed;
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

	//What type of Enemy is it? (0 = Bloater, 1 = Chaser, 2 = Crawler)
	int m_Type;

	//Behavior-specific variables
	int m_bowserFreezeTime = 0;
	bool m_fishBoosting = false;

	//Stringstream to calculate which texture should be used based on angle
	std::stringstream m_directionFacingStream;

	// Public prototypes go here	
public:

	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	//Get the the cardinal direction the sprite is facing
	std::string getDirection(float angle);

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation);
};


