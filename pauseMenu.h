#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

#define MAX_NUMBER_OF_ITEMS 3
#define PosX -200
#define PosY -180
#define Gap 130

class pauseMenu
{
public:
	pauseMenu(Font* font);
	~pauseMenu();
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void pauseActive(Vector2f pos);
	int GetPressedItem() { return selectedItemIndex; }
private:
	RectangleShape bg;
	int selectedItemIndex;
	Text text[MAX_NUMBER_OF_ITEMS],head;
};

