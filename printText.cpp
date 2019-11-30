#include "printText.h"

printText::printText(Font* font)
{
	string ttf("Res/Fonts/");
	score.setCharacterSize(40);
	score.setOutlineThickness(2);
	score.setOutlineColor(Color::Black);
	score.setFillColor(Color::Red);
	score.setFont(*font);
	
	point = 0;
}

printText::~printText()
{
}

void printText::setPosition(Vector2f pos)
{
	score.setPosition(pos.x + 700,pos.y - 530);
	
}

void printText::Draw(RenderWindow& window)
{
	window.draw(score);
}

void printText::setValue()
{
	stringstream ssPoint;
	ssPoint << "Score : " << point << endl;
	score.setString(ssPoint.str());
}
