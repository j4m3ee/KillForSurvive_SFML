#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

class Print
{
public:
	Print();
	~Print();
	void Draw(RenderWindow& window);
	void Update(float value,Vector2f Pos);

private:
	Font font;
	Text text;
	stringstream ss;
};

