#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
using namespace sf;

class Collider
{
public:
	Collider(RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider other, float push);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; }


private:
	RectangleShape& body;
};