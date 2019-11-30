#include "pauseMenu.h"

pauseMenu::pauseMenu(Font* font)
{
	string ttf("Res/Fonts/");

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		text[i].setFont(*font);
		text[i].setOutlineThickness(5);
		text[i].setOutlineColor(Color::Black);
		text[i].setCharacterSize(70);
	}
	head.setFont(*font);
	head.setOutlineThickness(5);
	head.setOutlineColor(Color::Black);
	head.setCharacterSize(90);
	head.setFillColor(Color(0, 204, 0, 255));
	head.setString("Pause Menu");

	text[0].setFillColor(Color::Red);
	text[0].setString("Continues");

	text[1].setFillColor(Color(200, 200, 200, 255));
	text[1].setString("Main Menu");

	text[2].setFillColor(Color(200, 200, 200, 255));
	text[2].setString("Exit");

	bg.setFillColor(Color(190, 190, 190, 150));
	bg.setSize(Vector2f(800.0f, 600.0f));
	bg.setOrigin(bg.getPosition() / 2.0f);

	selectedItemIndex = 0;
}

pauseMenu::~pauseMenu()
{
}

void pauseMenu::draw(RenderWindow& window)
{
	window.draw(bg);
	window.draw(head);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(text[i]);
	}
}

void pauseMenu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		text[selectedItemIndex].setFillColor(Color(200, 200, 200, 255));
		selectedItemIndex--;
		text[selectedItemIndex].setFillColor(Color::Red);
	}
}

void pauseMenu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		text[selectedItemIndex].setFillColor(Color(200, 200, 200, 255));
		selectedItemIndex++;
		text[selectedItemIndex].setFillColor(Color::Red);
	}
}

void pauseMenu::pauseActive(Vector2f pos)
{

	text[0].setPosition(Vector2f(pos.x + PosX, pos.y + PosY + (0 * Gap)));

	text[1].setPosition(Vector2f(pos.x + PosX, pos.y + PosY + (1 * Gap)));

	text[2].setPosition(Vector2f(pos.x + PosX, pos.y + PosY + (2 * Gap)));

	bg.setPosition(Vector2f(pos.x -400.0f, pos.y -400.0f));

	head.setPosition(Vector2f(pos.x - 250.0f, pos.y - 350.0f));
}
