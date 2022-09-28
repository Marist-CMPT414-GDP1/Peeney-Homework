#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Pong", Style::Default);

	int score = 0;
	int lives = 3;

	//Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);

	//WE WILL ADD A BALL LATER

	Text hud;
	Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	Clock clock;

	while (window.isOpen()) {
		/*
		========== HANDLE THE PLAYER'S INPUT ==========
		*/

		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}

		/*
		========== UPDATE THE BAT, BALL, AND HUD ==========
		*/

		//Update the delta time
		Time dt = clock.restart();
		bat.update(dt);

		std::stringstream ss;
		ss << "Score:" << score << "   Lives:" << lives;
		hud.setString(ss.str());

		/*
		========== DRAW THE BAT, BALL, AND HUD ==========
		*/

		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.display();
	}

	return 0;

}