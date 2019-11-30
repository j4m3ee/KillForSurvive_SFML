#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Collider.h"

using namespace sf;
using namespace std;

class Item
{
public:
	Item(Texture* texture);
	~Item();

	void Draw(RenderWindow& window);
	void setPosition(Vector2f Pos, int Type);

	Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(hitBlock); }

	int getType() { return type; }

private:
	RectangleShape body, hitBlock;
	IntRect uvRect;
	int type;
};

