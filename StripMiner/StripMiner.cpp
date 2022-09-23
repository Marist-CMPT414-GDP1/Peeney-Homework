#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//Function prototypes
void updateSpiders();

//Prepare spiders
const int NUM_SPIDERS = 9;
Sprite spiders[NUM_SPIDERS];

//Prepare stone strips
Sprite strips[3];
enum class strip { TOP, CENTER, BOTTOM, NONE };
strip spiderPositions[NUM_SPIDERS];

int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Strip Miner", Style::Default);
	//Need to figure out how to adapt resolution

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
	strips[0].setPosition(0, 150);
	strips[1].setPosition(0, 450);
	strips[2].setPosition(0, 750);

	//Prepare spiders
	Texture textureSpider;
	textureSpider.loadFromFile("graphics/spider.png");

	//Set the texture for each spider
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
	bool beeActive = false;
	float beeSpeed = 0.0f;

	//Prepare clouds - need to change this graphic and use an array instead
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;

	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Variables to control time itself
	Clock clock;

	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::White);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 4.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	bool paused = true;

	//Prepare text
	int score = 0;

	Text messageText;
	Text scoreText;

	//Choose a font
	Font font;
	font.loadFromFile("fonts/Minecraft.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);


	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

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
	texturePlayer.loadFromFile("graphics/steve_side.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(1650, 750);

	//The player starts at the bottom
	strip playerstrip = strip::BOTTOM;

	//Prepare the death graphic
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(2000, 0);

	//Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/pickaxe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(2000, 0);

	//Line the axe up with the stone strips
	const float AXE_POSITION_TOP = 205;
	const float AXE_POSITION_CENTER = 505;
	const float AXE_POSITION_BOTTOM = 805;

	//Prepare the flying cobblestone
	Texture textureCobble;
	textureCobble.loadFromFile("graphics/cobblestone.png");
	Sprite spriteCobble;
	spriteCobble.setTexture(textureCobble);
	spriteCobble.setPosition(2000, 0);

	//Some other useful cobble related variables
	bool cobbleActive = false;
	float cobbleSpeedX = 1000;
	float cobbleSpeedY = -1500;

	//Control the player input
	bool acceptInput = false;

	//Prepare the sounds
	//break1.wav
	SoundBuffer break1Buffer;
	break1Buffer.loadFromFile("sound/break1.wav");
	Sound break1;
	break1.setBuffer(break1Buffer);

	//break2.wav
	SoundBuffer break2Buffer;
	break2Buffer.loadFromFile("sound/break2.wav");
	Sound break2;
	break2.setBuffer(break2Buffer);

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
				spriteAxe.setPosition(2000, 0);
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
			timeRemaining = 4;

			//Make all spiders disappear, starting in the second position
			for (int i = 1; i < NUM_SPIDERS; i++)
			{
				spiderPositions[i] = strip::NONE;
			}

			//Make sure the gravestone is hidden
			spriteRIP.setPosition(2000, 0);

			//Move the player into position
			spritePlayer.setPosition(1650, 750);

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
					spritePlayer.setPosition(1650, 150);
					spriteAxe.setPosition(1600, AXE_POSITION_TOP);
					spriteCobble.setPosition(1500, 180);
				}

				else if (Keyboard::isKeyPressed(Keyboard::K))
				{
					playerstrip = strip::CENTER;
					spritePlayer.setPosition(1650, 450);
					spriteAxe.setPosition(1600, AXE_POSITION_CENTER);
					spriteCobble.setPosition(1500, 480);
				}

				else if (Keyboard::isKeyPressed(Keyboard::M))
				{
					playerstrip = strip::BOTTOM;
					spritePlayer.setPosition(1650, 750);
					spriteAxe.setPosition(1600, AXE_POSITION_BOTTOM);
					spriteCobble.setPosition(1500, 780);
				}
				
				score++;

				//Add to the amount of time remaining
				timeRemaining += (1 / score) + .16;

				//Update the spiders
				updateSpiders();

				//Set the cobble flying
				cobbleSpeedX = 2500;
				cobbleActive = true;

				acceptInput = false;

				//Breaking stone sound

				int r = (rand() % 2);
				if (r == 0)
					break1.play();
				else
					break2.play();
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
					spiders[i].setPosition(spiderX, 250);
				}
				else if (spiderPositions[i] == strip::CENTER)
				{
					spiders[i].setPosition(spiderX, 550);
				}
				else if (spiderPositions[i] == strip::BOTTOM)
				{
					spiders[i].setPosition(spiderX, 850);
				}
				else
				{
					//Hide the spider
					spiders[i].setPosition(spiderX, 3000);
				}
			}

			//Handle a flying cobble
			if (cobbleActive)
			{
				spriteCobble.setPosition(
					spriteCobble.getPosition().x + (cobbleSpeedX * dt.asSeconds()),
					spriteCobble.getPosition().y + (cobbleSpeedY * dt.asSeconds())
				);

				//Has the cobble reached an edge of the screen?
				if (spriteCobble.getPosition().x < -100 || spriteCobble.getPosition().x > 2000)
				{
					//Set it up to be a whole new cobble next frame
					cobbleActive = false;
					spriteCobble.setPosition(2000, 720);
				}
			}

			//Has the player been bitten by a spider?
			if (spiderPositions[NUM_SPIDERS - 1] == playerstrip)
			{
				//death
				paused = true;
				acceptInput = false;

				//Draw the gravestone
				spriteRIP.setPosition(spritePlayer.getPosition().x, spritePlayer.getPosition().y);

				//Hide the player
				spritePlayer.setPosition(2000, 0);

				//Hide the axe
				spriteAxe.setPosition(2000, 0);

				//Hide the cobble
				spriteCobble.setPosition(2000, 0);

				//Change the text of the message
				messageText.setString("BITTEN!");

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

		//Draw the flying cobble
		window.draw(spriteCobble);

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

	//Spawn a new spider at position 0
	int r = (rand() % 5);

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