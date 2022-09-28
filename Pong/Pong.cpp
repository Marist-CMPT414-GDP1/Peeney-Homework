#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Pong", Style::Default);

	int score = 0;
	int lives = 3;

	//Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);

	//WE WILL ADD A BALL LATER

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

		/*
		========== UPDATE THE BAT, BALL, AND HUD ==========
		*/

		/*
		========== DRAW THE BAT, BALL, AND HUD ==========
		*/
	}

	return 0;

}