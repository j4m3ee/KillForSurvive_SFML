#include "dropPlane.h"

dropPlane::dropPlane(Texture* planeTex,float speed)
{
	this->speed = speed;
	body.setSize(Vector2f(300.0f, 300.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(planeTex);
	body.setRotation(90.0f);
}

dropPlane::~dropPlane()
{
}

void dropPlane::Update(float deltaTime, Vector2f view)
{
	Vector2f movement(0.0f, 0.0f);
	movement.x += speed;
	body.move(movement * deltaTime);
}

void dropPlane::Draw(RenderWindow& window)
{
	window.draw(body);
}

void dropPlane::setPosition(Vector2f pos)
{
	body.setPosition(pos);
}
