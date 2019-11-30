#include "Platform.h"

Platform::Platform(Texture* texture, Vector2f size, Vector2f sizeHit, Vector2f possition)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	hitblock.setSize(sizeHit );
	hitblock.setOrigin(sizeHit / 2.0f);
	hitblock.setPosition(possition);
	body.setPosition(possition);
}

Platform::~Platform()
{
}

void Platform::Draw(RenderWindow & window)
{
	window.draw(body);
}

void Platform::setPosition(Vector2f startPos)
{
	body.setPosition(startPos);
	hitblock.setPosition(startPos);
}

bool Platform::Hiding(Vector2f playerPos)
{
	bodyPos = hitblock.getPosition();
	Vector2f otherPosition = playerPos;
	Vector2f otherHalfSize(30.0f, 30.0f);
	Vector2f thisPosition = bodyPos;
	Vector2f thisHalfSize = hitblock.getSize() / 2.0f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		return true;
	}
	else return false;
}


