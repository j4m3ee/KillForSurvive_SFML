#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

#define MAX_NUMBER_OF_ITEMS 4
#define PosX 300
#define PosY 340
#define Gap 130


class Menu
{
public:
	Menu(Font* font);
	~Menu();

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	Text text[MAX_NUMBER_OF_ITEMS];
};

