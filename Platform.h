#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
using namespace sf;

class Platform
{
public:
	Platform(Texture * texture,Vector2f size, Vector2f sizeHit,Vector2f possition);
	~Platform();

	void Draw(RenderWindow& window);
	void setPosition(Vector2f startPos);
	Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(hitblock); }
	
	bool Hiding(Vector2f playerPos);

private:
	RectangleShape body,hitblock;
	Vector2f bodyPos;
};

