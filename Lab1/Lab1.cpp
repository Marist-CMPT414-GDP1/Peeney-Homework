//Justin Peeney
//GDP1
//Lab1
//9-8-22

#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	//set up the window
	VideoMode vm(400, 300);
	RenderWindow window(vm, "Hello World!", Style::Default);

	//set up the text
	Text message;
	message.setString("Hello World!");

	message.setCharacterSize(40);
	message.setFillColor(Color::White);

	Text timer;
	timer.setString("10");
	
	timer.setCharacterSize(30);
	timer.setFillColor(Color::White);

	//position the text
	
	FloatRect textRect = message.getLocalBounds();

	message.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);
	
	message.setPosition(50, 300 / 2.0f);

	timer.setPosition(20, 20);

	//set up the font
	Font font;
	font.loadFromFile("SuperMario256.ttf");
	message.setFont(font);
	timer.setFont(font);

	//draw the text
	window.draw(message);
	window.draw(timer);

	Clock clock;
	int timeRemaining = 10;
	Time dt = clock.restart();

	window.display();
	
	
	while (window.isOpen())
	{
		
		timer.setString(std::to_string(timeRemaining));
		window.draw(timer);
		timeRemaining -= dt.asSeconds();
		//if (timeRemaining < 1) {
			//return 0;
		//}
		//display a countdown of 10 to 0 seconds
		//will need to window.display() after every update I think?
		//close the program with the return statement below
		//return 0;
	
	}
}