//Right now the player dies when there's a spider around the center on the same strip.


//Include important libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Make code easier to type with "using namespace"
using namespace sf;

//Function prototypes
void updateSpiders();

const int NUM_SPIDERS = 8;
Sprite spiders[NUM_SPIDERS];

Sprite strips[3];

//Where is the player/spiders?
enum class strip { TOP, CENTER, BOTTOM, NONE };
strip spiderPositions[NUM_SPIDERS];

int main()
{
	//Create a video mode object
	VideoMode vm(1920, 1080);

	//Create and open a window for the game
	RenderWindow window(vm, "Strip Miner", Style::Default);
	//Changed this to Default temporarily bc Fullscreen is acting strangely

	Texture textureBackground;
	textureBackground.loadFromFile("graphics/mc_bg.jpg");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//Set up the 3 stone strips
	Texture textureStrip;
	textureStrip.loadFromFile("graphics/stone_strip.png");

	for (int i = 0; i < 3; i++) {
		strips[i].setTexture(textureStrip);
	}
	strips[0].setPosition(400, 150);
	strips[1].setPosition(400, 450);
	strips[2].setPosition(400, 750);

	//Prepare 8 spiders
	Texture textureSpider;
	textureSpider.loadFromFile("graphics/spider.png");

	//Set the texture for each branch sprite
	for (int i = 0; i < NUM_SPIDERS; i++) {
		spiders[i].setTexture(textureSpider);
		spiders[i].setPosition(-2000, -2000);
		spiders[i].setOrigin(100, 78);
	}

	//Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	//Is the bee currently moving?
	bool beeActive = false;

	//How fast can the bee fly
	float beeSpeed = 0.0f;

	//Make 3 cloud sprites from 1 texture
	Texture textureCloud;

	//Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");

	//3 new sprites from with the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	//Position the clouds on the left of the screen at diff heights
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	//Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	//How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Variables to control time itself
	Clock clock;

	//Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::White);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Track whether the game is running
	bool paused = true;

	//Draw some text
	int score = 0;

	Text messageText;
	Text scoreText;

	//Choose a font
	Font font;
	font.loadFromFile("fonts/Minecraft.ttf");

	//Apply the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	//Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	//Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	//Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	//Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	//The player starts on the left
	strip playerstrip = strip::TOP;

	//Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	//Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//Line the axe up with the tree
	const float AXE_POSITION_TOP = 150;
	const float AXE_POSITION_CENTER = 350;
	const float AXE_POSITION_BOTTOM = 750;

	//Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	//Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	//Control the player input
	bool acceptInput = false;

	//Prepare the sounds
	//chop.wav
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	//death.wav
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	//out_of_time.wav
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	while (window.isOpen())
	{

		/*
		*************************
		HANDLE THE PLAYER'S INPUT
		*************************
		*/

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				//Listen for key presses again
				acceptInput = true;

				//Hide the axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			//Reset the time and score
			score = 0;
			timeRemaining = 6;

			//Make all spiders disappear, starting in the second position
			for (int i = 1; i < NUM_SPIDERS; i++)
			{
				spiderPositions[i] = strip::NONE;
			}

			//Make sure the gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			//Move the player into position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;

		}

		//Wrap the player controls to make sure we are accepting input
		if (acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::O)
				|| Keyboard::isKeyPressed(Keyboard::K)
				|| Keyboard::isKeyPressed(Keyboard::M))
			{
				if (Keyboard::isKeyPressed(Keyboard::O))
				{
					playerstrip = strip::TOP;
					spritePlayer.setPosition(0, 150);
					spriteAxe.setPosition(spriteAxe.getPosition().x, AXE_POSITION_TOP);
				}

				else if (Keyboard::isKeyPressed(Keyboard::K))
				{
					playerstrip = strip::CENTER;
					spritePlayer.setPosition(0, 350);
					spriteAxe.setPosition(spriteAxe.getPosition().x, AXE_POSITION_CENTER);
				}

				else if (Keyboard::isKeyPressed(Keyboard::M))
				{
					playerstrip = strip::BOTTOM;
					spritePlayer.setPosition(0, 750);
					spriteAxe.setPosition(spriteAxe.getPosition().x, AXE_POSITION_BOTTOM);
				}
				
				score++;

				//Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				//Update the spiders
				updateSpiders();

				//Set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				//Chop sound
				chop.play();
			}
		}

		/*
		****************
		UPDATE THE SCENE
		****************
		*/

		if (!paused)
		{

			//Measure time
			Time dt = clock.restart();

			//Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();

			//Resize the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				//Pause the game
				paused = true;

				//Change the message shown to the player
				messageText.setString("Out of time!");

				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f
				);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				//Out of time sound
				outOfTime.play();
			}

			//Setup the bee
			if (!beeActive)
			{
				//How fast is the bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				//How high is the bee
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
				//Move the bee
			{
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y
				);

				//Has the bee reached the left edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					//Set it up ready to be a whole new bee next frame
					beeActive = false;
				}
			}

			//Manage the clouds
			//Cloud 1
			if (!cloud1Active)
			{
				//How fast is the cloud
				cloud1Speed = (rand() % 200);

				//How high is the cloud
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y
				);

				//Has the cloud reached the right edge of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					//Set it up to be a whole new cloud next frame
					cloud1Active = false;
				}
			}

			//Cloud 2
			if (!cloud2Active)
			{
				//How fast is the cloud
				cloud2Speed = (rand() % 200);

				//How high is the cloud
				float height = (rand() % 150);
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y
				);

				//Has the cloud reached the right edge of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					//Set it up to be a whole new cloud next frame
					cloud2Active = false;
				}
			}

			//Cloud 3
			if (!cloud3Active)
			{
				//How fast is the cloud
				cloud3Speed = (rand() % 200);

				//How high is the cloud
				float height = (rand() % 150);
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y
				);

				//Has the cloud reached the right edge of the screen?
				if (spriteCloud3.getPosition().x > 1920)
				{
					//Set it up to be a whole new cloud next frame
					cloud3Active = false;
				}
			}

			//Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			//Update the spider sprites
			for (int i = 0; i < NUM_SPIDERS; i++)
			{
				float spiderX = i * 200;
				if (spiderPositions[i] == strip::TOP)
				{
					spiders[i].setPosition(spiderX, 150);
				}
				else if (spiderPositions[i] == strip::CENTER)
				{
					spiders[i].setPosition(spiderX, 450);
				}
				else if (spiderPositions[i] == strip::BOTTOM)
				{
					spiders[i].setPosition(spiderX, 750);
				}
				else
				{
					//Hide the spider
					spiders[i].setPosition(spiderX, 3000);
				}
			}

			//Handle a flying log
			if (logActive)
			{
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
				);

				//Has the log reached an edge of the screen?
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					//Set it up to be a whole new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			//Has the player been squished by a branch?
			if (spiderPositions[5] == playerstrip)
			{
				//death
				paused = true;
				acceptInput = false;

				//Draw the gravestone
				spriteRIP.setPosition(525, 760);

				//Hide the player
				spritePlayer.setPosition(2000, 660);

				//Change the text of the message
				messageText.setString("SQUISHED!");

				//Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f
				);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				//Death sound
				death.play();
			}

		} //End if(!paused)

		/*
		**************
		DRAW THE SCENE
		**************
		*/

		//Clear everything from the last frame
			//Clearing and then drawing is called "double buffering"
			//This prevents a graphical glitch called "tearing"
		window.clear();

		//Draw our game scene here
		window.draw(spriteBackground);

		//Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		for (int i = 0; i < 3; i++)
		{
			window.draw(strips[i]);
		}

		//Draw the spiders
		for (int i = 0; i < NUM_SPIDERS; i++)
		{
			window.draw(spiders[i]);
		}

		//Draw the player
		window.draw(spritePlayer);

		//Draw the axe
		window.draw(spriteAxe);

		//Draw the flying log
		window.draw(spriteLog);

		//Draw the gravestone
		window.draw(spriteRIP);

		//Draw the bee
		window.draw(spriteBee);

		//Draw the score
		window.draw(scoreText);

		//Draw the timebar
		window.draw(timeBar);

		if (paused) {
			//Draw our message
			window.draw(messageText);
		}

		//Show everything we just drew
		window.display();
	}

	return 0;
}

//Function definition
void updateSpiders()
{
	//Move all the spiders down one place
	for (int j = NUM_SPIDERS - 1; j > 0; j--)
	{
		spiderPositions[j] = spiderPositions[j - 1];
	}

	//Spawn a new branch at position 0
	int r = (rand() % 7);

	switch (r) {
	case 0:
		spiderPositions[0] = strip::TOP;
		break;

	case 1:
		spiderPositions[0] = strip::CENTER;
		break;

	case 2:
		spiderPositions[0] = strip::BOTTOM;
		break;

	default:
		spiderPositions[0] = strip::NONE;
		break;
	}
}