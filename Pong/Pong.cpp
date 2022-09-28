#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

//using namespace sf;

int main() {
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Pong", Style::Default);

	int score = 0;
	int lives = 3;
	bool allowScoring = false;

	//Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);

	//Create a ball
	Ball ball(1920 / 2, 0);

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
		ball.update(dt);

		std::stringstream ss;
		ss << "Score:" << score << "   Lives:" << lives;
		hud.setString(ss.str());

		//Handle the ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			//reverse the ball direction
			ball.reboundBottom();
			allowScoring = false;

			lives--;

			if (lives < 1)
			{
				score = 0;
				lives = 3;
			}
		}

		//Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			if (allowScoring)
			{
				score++;
			}
		}

		//Handle ball hitting sides
		if (ball.getPosition().left < 0 ||
			ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			ball.reboundSides();
		}

		//Has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			ball.reboundBatOrTop();
			allowScoring = true;
		}

		/*
		========== DRAW THE BAT, BALL, AND HUD ==========
		*/

		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;

}