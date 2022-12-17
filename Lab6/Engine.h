#pragma once
#include <SFML/Graphics.hpp>
#include "Goblin.h"
#include "GoblinGrunt.h"
#include "GoblinBruiser.h"
#include "Target.h"
#include "Hazard.h"

using namespace sf;

class Engine
{
private:
	// Declaration of the goblins
	//Instantiate one of each kind of Goblin subclass, 
	//and store pointers to these instances in an array.
	static const int NUM_GOBLINS = 2;
	Goblin* grunt = new GoblinGrunt;
	Goblin* bruiser = new GoblinBruiser;
	Goblin* goblinArray[NUM_GOBLINS] = { grunt, bruiser };
	Goblin* currentGoblin = goblinArray[0];

	Target target = Target({ 100, 200 });
	Hazard hazard = Hazard({ 400, 400 });

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