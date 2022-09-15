//Justin Peeney
//GDP1
//Lab1
//9-8-22

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	//set up the window
	VideoMode vm(400, 300);
	RenderWindow window(vm, "Hello World!", Style::Default);

	//set up the clock
	Clock clock;
	int timeRemaining = 10;

	//set up the text
	Text message;
	message.setString("Hello World!");

	message.setCharacterSize(40);
	message.setFillColor(Color::White);

	Text timer;
	timer.setString(std::to_string(timeRemaining));
	
	timer.setCharacterSize(30);
	timer.setFillColor(Color::White);

	//set up the font
	Font font;
	font.loadFromFile("SuperMario256.ttf");
	message.setFont(font);
	timer.setFont(font);

	//position the text
	FloatRect textRect = message.getLocalBounds();

	message.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);
	
	message.setPosition(400 / 2.0f, 300 / 2.0f);

	timer.setPosition(20, 20);
	
	while (window.isOpen())
	{
		if (clock.getElapsedTime().asSeconds() >= 1.0f) 
		{
			timeRemaining--;
			clock.restart();
		}

		if (timeRemaining < 1) {
			return 0;
		}

		timer.setString(std::to_string(timeRemaining));

		window.clear();
		window.draw(message);
		window.draw(timer);
		window.display();
	}
}