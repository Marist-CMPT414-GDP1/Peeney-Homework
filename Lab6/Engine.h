#pragma once
#include <SFML/Graphics.hpp>
#include "Goblin.h"
#include "GoblinGrunt.h"
#include "GoblinBruiser.h"

using namespace sf;

class Engine
{
private:
	// Declaration of the goblins
	//Instantiate one of each kind of Goblin subclass, 
	//and store pointers to these instances in an array.
	GoblinGrunt grunt;
	GoblinBruiser bruiser;
	Goblin* currentGoblin = &grunt;
	//Goblin goblins[4];

	RenderWindow m_Window;
	View m_View;

	// Is the game currently playing?
	bool m_Playing = false;

	// Character

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();


public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};