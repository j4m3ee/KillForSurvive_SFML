#include "Print.h"

Print::Print()
{
	string ttf("Res/Fonts/");
	if (!font.loadFromFile(ttf + "Cascadia.ttf")) {
		//Error
	}

	text.setFont(font);
	text.setOutlineThickness(5);
	text.setOutlineColor(Color::Black);
	text.setCharacterSize(50);
}

Print::~Print()
{
}

void Print::Draw(RenderWindow& window)
{
	window.draw(text);
}

void Print::Update(float value, Vector2f Pos)
{
	text.setPosition(Pos);
	
	ss << "HP : " << value << endl;

	text.setString(ss.str());
}
