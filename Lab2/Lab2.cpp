//Justin Peeney
//GDP1
//Lab2
//9-15-22

#include <SFML/Graphics.hpp>

using namespace sf;

const int NUM_SPRITES = 9; //number of sprites in the ring
Sprite sprites[NUM_SPRITES];

//Offset to space the sprites apart
//Multiplicative constant to angleRadianIncrease
const int SPRITE_OFFSET = 40;

int main()
{
	//Set up variables
	int centerX = 250;
	int centerY = 250;
	int radius = 100;

	double angle = 0;
	double angleRadianIncrease = 0.0174533;

	//Set up the window
	VideoMode vm(500, 500);
	RenderWindow window(vm, "Lab2", Style::Default);

	//Set up the bee sprite
	Texture textureBee;
	textureBee.loadFromFile("bee.png");
	

	for (int i = 0; i < NUM_SPRITES; i++) {
		sprites[i].setTexture(textureBee);
		sprites[i].setOrigin(30, 20);
	}

	Clock clock;
	float timeInterval = 5; //in milliseconds

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (clock.getElapsedTime().asMilliseconds() >= timeInterval)
		{
			angle = angle + angleRadianIncrease;
			clock.restart();
		}

		for (int i = 0; i < NUM_SPRITES; i++) 
		{
			sprites[i].setPosition(
				centerX + radius * cos(angle - angleRadianIncrease * SPRITE_OFFSET * i),
					centerY + radius * sin(angle - angleRadianIncrease * SPRITE_OFFSET * i)
					);
		}

		window.clear();

		for (int i = 0; i < NUM_SPRITES; i++) {
			window.draw(sprites[i]);
		}

		window.display();
	}
}