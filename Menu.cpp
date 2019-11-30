#include "Menu.h"

Menu::Menu(Font* font) {
	string ttf("Res/Fonts/");

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		text[i].setFont(*font);
		text[i].setOutlineThickness(5);
		text[i].setOutlineColor(Color::Black);
		text[i].setCharacterSize(70);
	}

	text[0].setFillColor(Color::Red);
	text[0].setString("Play");
	text[0].setPosition(Vector2f(PosX,PosY + (0*Gap)));

	text[1].setFillColor(Color(200, 200, 200, 255));
	text[1].setString("How To Play");
	text[1].setPosition(Vector2f(PosX, PosY + (1 * Gap)));

	text[2].setFillColor(Color(200, 200, 200, 255));
	text[2].setString("High Score");
	text[2].setPosition(Vector2f(PosX, PosY + (2 * Gap)));

	text[3].setFillColor(Color(200, 200, 200, 255));
	text[3].setString("Exit");
	text[3].setPosition(Vector2f(PosX, PosY + (3 * Gap)));
	
	selectedItemIndex = 0;
}

Menu::~Menu() {

}

void Menu::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(text[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		text[selectedItemIndex].setFillColor(Color(200, 200, 200, 255));
		selectedItemIndex--;
		text[selectedItemIndex].setFillColor(Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		text[selectedItemIndex].setFillColor(Color(200, 200, 200, 255));
		selectedItemIndex++;
		text[selectedItemIndex].setFillColor(Color::Red);
	}
}