#include "Bullet.h"

Bullet::Bullet(Texture* texture) 
	: currVelocity(0.0f, 0.0f), maxSpeed(10.0f)
{
	//row = 0;

	body.setSize(Vector2f(10.0f, 10.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	
}

Bullet::~Bullet()
{
}

void Bullet::Update(Vector2f currVelocity)
{
	Vector2f movement(0.0f, 0.0f);

	body.move(currVelocity);
}

void Bullet::Draw(RenderWindow& window)
{
	window.draw(body);
}

void Bullet::setPosition(Vector2f startPos, float damage)
{
	body.setPosition(startPos.x, startPos.y);
	this->damage = damage;
	//cout << degree << " " << startPos.x << " " << startPos.y << endl;
}
