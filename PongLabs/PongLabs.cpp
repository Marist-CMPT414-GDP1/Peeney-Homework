//Justin Peeney
//GDP1
//Lab3 - Gone Batty Part 2
//10-13-22

#include <SFML/Graphics.hpp>
#include "Saber.h"
#include "Laser.h"
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace sf;

enum class state {MENU, PLAY, GAMEOVER};
enum class lastRebound {TOP, BOTTOM, RIGHT, SABER, NONE};

const float LASER_START_X = 1720;
const float LASER_START_Y = 1080 / 2;

int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "PongLabs",Style::Default);
	//View view(FloatRect(0, 0, 1920, 1080));
	//coordinates of upper left corner, width and height
	//window.setView(view);

	int score = 0;
	int lives = 3;
	float cooldown = 0;
	bool allowScoring = false;

	state state = state::MENU;
	lastRebound lastRebound = lastRebound::NONE;

	//Create a saber
	Saber saber(20, 1080 / 4);

	//Create the laser
	Laser laser(LASER_START_X, LASER_START_Y);

	Text hud;
	Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	Sprite spriteScreen;
	Texture textureScreen;
	textureScreen.loadFromFile("graphics/screen.png");
	spriteScreen.setTexture(textureScreen);

	Text screenText;
	screenText.setFont(font);
	screenText.setCharacterSize(100);
	screenText.setFillColor(Color::White);
	screenText.setPosition(20, 20);

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
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter) && state != state::PLAY)
		{
			laser.resetLaser(LASER_START_X, LASER_START_Y);
			std::cerr << "Reset laser after pressing enter" << std::endl;
			score = 0;
			lives = 3;
			lastRebound = lastRebound::NONE;
			clock.restart();
			state = state::PLAY;
		}

		if (state == state::PLAY)
		{

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

			if (Keyboard::isKeyPressed(Keyboard::Space) && !saber.getPowerState() && cooldown == 0)
			{
				saber.powerUp();
			}
		}

			/*
			========== UPDATE THE SABER, LASER, AND HUD ==========
			*/

		if (state == state::PLAY) {

			//Update the delta time
			Time dt = clock.restart();
			saber.update(dt);
			laser.update(dt, saber.getPowerState());

			//Update power-up cooldown timer
			if (cooldown > 0)
			{
				cooldown -= dt.asSeconds();
			}
			if (cooldown < 1)
			{
				cooldown = 0;
			}

			std::stringstream ss;
			ss << "Score:" << score << "   Lives:" << lives << "   Cooldown:" << (int)cooldown;
			hud.setString(ss.str());

			//Handle the ball hitting the left
			if (laser.getPosition().left < 0)
			{
				laser.resetLaser(LASER_START_X, LASER_START_Y);
				std::cerr << "Reset laser because it touched the left edge" << std::endl;
				lastRebound = lastRebound::NONE;
				allowScoring = false;

				lives--;
				std::cerr << "Lost a life, lives = " << lives << std::endl;

				if (lives < 1)
				{
					state = state::GAMEOVER;
					score = 0;
					lives = 3;
					cooldown = 0;
				}
			}

			//Handle ball hitting the right
			if (laser.getPosition().left + laser.getPosition().width > window.getSize().x
				&& lastRebound != lastRebound::RIGHT)
			{
				laser.reboundRight();
				lastRebound = lastRebound::RIGHT;
				if (allowScoring)
				{
					score++;
				}
			}

			//Handle laser hitting top
			if (laser.getPosition().top < 0 && lastRebound != lastRebound::TOP)
			{
				laser.reboundEdges();
				lastRebound = lastRebound::TOP;
			}

			//Handle laser hitting bottom
			if (laser.getPosition().top + laser.getPosition().height > window.getSize().y
				&& lastRebound != lastRebound::BOTTOM)
			{
				laser.reboundEdges();
				lastRebound = lastRebound::BOTTOM;
			}

			//Has the laser hit the saber?
			if (laser.getPosition().intersects(saber.getDimensions())
				&& lastRebound != lastRebound::SABER)
			{
				laser.reboundSaber();
				if (saber.getPowerState())
				{
					saber.powerDown();
					cooldown = 11;
				}
				lastRebound = lastRebound::SABER;
				allowScoring = true;
			}
		}
		else if (state == state::MENU)
		{
			screenText.setString("Press Enter to start\n\nPressing the Spacebar powers up\nyour lightsaber for a stronger hit");
		}
		else
		{
			screenText.setString("Game Over\nPress Enter to retry");
		}

		/*
		========== DRAW THE SABER, LASER, AND HUD ==========
		*/

		window.clear();
		if (state == state::PLAY) {
			window.draw(hud);
			window.draw(saber.getSprite());
			window.draw(laser.getSprite());
		}
		else
		{
			window.draw(spriteScreen);
			window.draw(screenText);
		}
		window.display();
	}

	return 0;
}