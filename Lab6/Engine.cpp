#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = 640;
	resolution.y = 640;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Goblin Party",
		Style::Default);

	// Initialize the full screen view
	m_View.setSize(resolution);
}

void Engine::run()
{
	// Timing 	
	Clock clock;

	//Spawn all the goblins in a for loop going through the array
	for (int i = 0; i < NUM_GOBLINS; ++i)
	{
		goblinArray[i]->spawn({0,0});
	}

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}

			// Handle the player starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				m_Playing = true;
			}

			//Handle switching goblins
			if (Keyboard::isKeyPressed(Keyboard::Num1))
			{
				currentGoblin = goblinArray[0];
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num2))
			{
				currentGoblin = goblinArray[1];
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num3))
			{

			}
			else if (Keyboard::isKeyPressed(Keyboard::Num4))
			{

			}
		}
	}

	// Handle input
	currentGoblin->handleInput();
}

void Engine::update(float dtAsSeconds)
{
	if (m_Playing)
	{
		currentGoblin->update(dtAsSeconds);

	}// End if playing
}

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	m_Window.draw(target.getShape());
	m_Window.draw(hazard.getShape());
	m_Window.draw(currentGoblin->getSprite());

	// Show everything we have just drawn
	m_Window.display();
}