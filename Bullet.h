#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Enermy.h"

using namespace sf;
using namespace std;

class Bullet
{
public:
	Bullet(Texture* texture);
	~Bullet();

	void Update(Vector2f currVelocity);
	void Draw(RenderWindow& window);
	void setPosition(Vector2f startPos,float damage);

	Vector2f currVelocity;
	float maxSpeed,damage;

	Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

private:
	RectangleShape body;
	Vector2f startPos;
};



