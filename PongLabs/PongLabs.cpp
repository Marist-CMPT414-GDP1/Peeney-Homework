//Justin Peeney
//GDP1
//Lab3 - Gone Batty Part 1
//9-29-22

#include <SFML/Graphics.hpp>
#include "Saber.h"

using namespace sf;

int main()
{
	VideoMode vm;
	RenderWindow window(vm, "PongLabs", Style::Fullscreen);
	View view(FloatRect(0, 0, 1920, 1080));
	//coordinates of upper left corner, width and height
	window.setView(view);

	//Create a saber
	Saber saber(20, 1080/4);

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
		========== UPDATE THE SABER ==========
		*/

		//Update the delta time
		Time dt = clock.restart();
		saber.update(dt);

		/*
		========== DRAW THE SABER ==========
		*/

		window.clear();
		window.draw(saber.getSprite());
		window.display();
	}

	return 0;
}