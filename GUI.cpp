#include "GUI.h"

GUI::GUI(float hight)
{
	this -> Hight = hight;

	HPbar.setFillColor(Color(255, 51, 51, 255));
	BgHp.setSize(Vector2f(100 * 2, hight));
	BgHp.setFillColor(Color(102, 102, 255, 255));
	BgHp.setOutlineThickness(2.0f);
	BgHp.setOutlineColor(Color::Black);
}

GUI::~GUI()
{
}

void GUI::Draw(RenderWindow& window)
{
	window.draw(BgHp);
	window.draw(HPbar);
}

void GUI::Update(float Long, Vector2f view, Vector2f pos)
{
	HPbar.setPosition(view.x + pos.x, view.y + pos.y);
	if (Long > 0) HPbar.setSize(Vector2f(Long * (float)2, Hight));
	else HPbar.setSize(Vector2f(0, 20));
	BgHp.setPosition(view.x + pos.x, view.y + pos.y);
	BgHp.setSize(Vector2f(100 * 2, Hight));
}
