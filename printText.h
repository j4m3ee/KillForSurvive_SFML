#pragma once
#include <iostream>
#include <sstream>
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;

class printText
{
public :
	printText(Font* font);
	~printText();
	void setPosition(Vector2f pos);
	void Draw(RenderWindow& window);
	void setValue();

	int point;

private:
	Text score;
	
};

