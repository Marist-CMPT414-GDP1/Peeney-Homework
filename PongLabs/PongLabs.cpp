//Justin Peeney
//GDP1
//Lab3 - Gone Batty Part 2
//10-13-22

#include <SFML/Graphics.hpp>
#include "Saber.h"
#include "Laser.h"
#include <sstream>
#include <cstdlib>

using namespace sf;

int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "PongLabs",Style::Default);
	//View view(FloatRect(0, 0, 1920, 1080));
	//coordinates of upper left corner, width and height
	//window.setView(view);

	int score = 0;
	int lives = 3;
	bool allowScoring = false;

	//Create a saber
	Saber saber(20, 1080 / 4);

	//Create the laser
	Laser laser(1720, 1080 / 2);

	Text hud;
	Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	Clock clock;

	while (window.isOpen())
	{
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

		if (Keyboard::isKeyPressed(Keyboard::Left)
			|| Keyboard::isKeyPressed(Keyboard::Right)
			|| Keyboard::isKeyPressed(Keyboard::Up)
			|| Keyboard::isKeyPressed(Keyboard::Down))
		{

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				saber.move(Saber::movement::LEFT);
			}

			else if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				saber.move(Saber::movement::RIGHT);
			}

			else if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				saber.move(Saber::movement::UP);
			}

			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				saber.move(Saber::movement::DOWN);
			}
		}
		else
		{
			saber.move(Saber::movement::NONE);
		}

		/*
		========== UPDATE THE SABER, LASER, AND HUD ==========
		*/

		//Update the delta time
		Time dt = clock.restart();
		saber.update(dt);
		laser.update(dt);

		std::stringstream ss;
		ss << "Score:" << score << "   Lives:" << lives;
		hud.setString(ss.str());

		//Handle the ball hitting the left
		if (laser.getPosition().left < 0)
		{
			laser.reboundLeft();
			allowScoring = false;

			lives--;

			if (lives < 1)
			{
				score = 0;
				lives = 3;
			}
		}

		//Handle ball hitting the right
		if (laser.getPosition().left + laser.getPosition().width > window.getSize().x)
		{
			laser.reboundRight();
			if (allowScoring)
			{
				score++;
			}
		}

		//Handle laser hitting edges
		if (laser.getPosition().top < 0 ||
			laser.getPosition().top + laser.getPosition().height > window.getSize().y)
		{
			laser.reboundEdges();
		}

		//Has the laser hit the saber?
		if (laser.getPosition().intersects(saber.getDimensions()))
		{
			laser.reboundSaber();
			allowScoring = true;
		}

		/*
		========== DRAW THE SABER, LASER, AND HUD ==========
		*/

		window.clear();
		window.draw(hud);
		window.draw(saber.getSprite());
		window.draw(laser.getSprite());
		window.display();
	}

	return 0;
}