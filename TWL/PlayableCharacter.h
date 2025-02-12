#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	//Which character is it
	int m_CharacterID;

	bool m_Stacked = false;

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	bool m_IsJumping;
	bool m_IsFalling;

	bool m_IsRespawning = false;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	//Is the player touching sticky floor
	bool m_Sticking = false;

	// Private variables and functions come next
private:
	
	// What is the gravity
	float m_Gravity;

	// How fast is the character
	float m_Speed = 400;

	// Where is the player
	Vector2f m_Position;
	Vector2f m_StartPosition;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// And a texture
	Texture m_Texture;

	// All our public functions will come next
public:

	void spawn(Vector2f startPosition, float gravity);

	// This is a pure virtual function
	bool virtual handleInput() = 0;
	// This class is now abstract and cannot be instanciated

	//Check if player is vulnerable to a block type
	bool virtual checkVulnerability(int blockID) = 0;

	// Where is the player
	FloatRect getRectangle();
	Vector2f getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Make the character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	//Change the stick state
	void stick();
	void unstick();

	//Change stacker
	void setStackState(bool stackState);

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);
};
