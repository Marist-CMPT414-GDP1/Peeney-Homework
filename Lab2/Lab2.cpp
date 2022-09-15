//Justin Peeney
//GDP1
//Lab2
//9-15-22

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	//Set up variables
	int centerX = 250;
	int centerY = 250;
	int radius = 100;

	int spriteX = centerX + radius;
	int spriteY = centerY + radius;

	double angle = 0;
	double angleRadianIncrease = 0.0174533;

	//Set up the window
	VideoMode vm(500, 500);
	RenderWindow window(vm, "Lab2", Style::Default);

	//Set up the bee sprite
	Texture textureBee;
	textureBee.loadFromFile("bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);

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

		int spriteX = centerX + radius * cos(angle);
		int spriteY = centerY + radius * sin(angle);

		spriteBee.setPosition(spriteX, spriteY);

		window.clear();
		window.draw(spriteBee);
		window.display();
	}
}