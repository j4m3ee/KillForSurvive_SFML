#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class GUI
{
public:
	GUI(float hight);
	~GUI();

	void Draw(RenderWindow& window);
	void Update(float Long , Vector2f view, Vector2f pos);

private:
	RectangleShape HPbar, BgHp;
	float Hight;
};

