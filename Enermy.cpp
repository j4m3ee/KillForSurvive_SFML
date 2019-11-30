#include "Enermy.h"

Enermy::Enermy(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime) 
{
	srand((unsigned int)time(0));
	this->speed = speed;
	row = 0;

	hp = 100.0f;
	drt = 0;
	dist = 100;
	cout = 0;
	fireRate = 0.5f; damage = 1.0f;

	body.setSize(Vector2f(313.0f / 3.0f, 207.0f / 3.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);

	hitBlock.setSize(Vector2f(45.0f, 45.0f));
	hitBlock.setOrigin(hitBlock.getSize() / 2.0f);
	hitBlock.setOutlineThickness(2.0f);
	hitBlock.setOutlineColor(Color::Black);
	hitBlock.setFillColor(Color::Transparent);

	HPbar.setFillColor(Color::Red);
	BgHp.setFillColor(Color::Blue);
	BgHp.setOutlineThickness(2.0f);
	BgHp.setOutlineColor(Color::Black);
}

Enermy::~Enermy()
{

}

void Enermy::Update(float deltaTime, Vector2f playerPos, float range, bool saw)
{
	Time = clock.getElapsedTime().asSeconds();

	bodyPos = body.getPosition();

	HPbar.setPosition(bodyPos.x-50,bodyPos.y-50);
	HPbar.setSize(Vector2f(hp, 5));
	BgHp.setPosition(bodyPos.x - 50, bodyPos.y - 50);
	BgHp.setSize(Vector2f(100, 5));

	Vector2f otherPosition = playerPos;
	Vector2f otherHalfSize(range, range);
	Vector2f thisPosition = bodyPos;
	Vector2f thisHalfSize = body.getSize() / 2.0f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	Vector2f movement(0.0f, 0.0f);

	if (intersectX < 0.0f && intersectY < 0.0f && saw == false )
	{
		if (Time > fireRate && shoot == true) {
			shoot = false;
			Time = clock.restart().asSeconds();
		}
		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {
				movement.x += speed;
			}
			else {
				movement.x -= speed;
			}
		}
		else {
			if (deltaY > 0.0f) {
				movement.y += speed;
			}
			else {
				movement.y -= speed;
			}
		}

		bodyPos = hitBlock.getPosition();
		const double PI = 3.14159265;
		float dx = playerPos.x - bodyPos.x;
		float dy = playerPos.y - bodyPos.y;
		float rotation = (atan2(dy, dx)) * 180 / (float)PI;
		body.setRotation(rotation);

	} else 
	{
		shoot = true;
		switch (drt) {
		case 1: //Up
			if (body.getPosition().y >= 100.0f) movement.y -= speed;
			body.setRotation(270);
			break;
		case 2: //Down
			if (body.getPosition().y <= 3900.0f)movement.y += speed;
			body.setRotation(90);
			break;
		case 3: //Left
			if (body.getPosition().x >= 100.0f) movement.x -= speed;
			else {
				drt = 4; dist = 500; cout = 0;
			}
				
			body.setRotation(180);
			break;
		case 4: //Right
			if (body.getPosition().x <= 3900.0f) movement.x += speed;
			body.setRotation(0);
			break;
		}
		cout++;
		if (cout >= dist) {
			drt = rand() % 4;
			dist = 50 + rand() % 200;
			cout = 0;
		}
	}

	if (movement.x == 0.0f) {
		row = 0;
	}
	else {
		row = 1;
	}

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	hitBlock.move(movement * deltaTime);
	body.setPosition(hitBlock.getPosition());
}

void Enermy::Draw(RenderWindow& window)
{
	window.draw(body);
	window.draw(BgHp);
	window.draw(HPbar);
}

void Enermy::UpdateTex(Texture* texture)
{
	switch (type)
	{
	case 0: //Piston
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(291.0f / 3.0f, 256.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.5f; damage = 5.0f;
		break;
	case 1: //Piston
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(291.0f / 3.0f, 256.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.5f; damage = 5.0f;
		break;
	case 2: //Piston
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(291.0f / 3.0f, 256.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.5f; damage = 5.0f;
		break;
	case 3: //Gloza
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(313.0f / 3.0f, 207.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.075f; damage = 5.0f;
		break;
	case 4: //Thomson
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(313.0f / 3.0f, 207.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.1f; damage = 6.0f;
		break;
	case 5: //AKM
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(313.0f / 3.0f, 207.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.15f; damage = 10.0f;
		break;
	case 6: //ShotGun
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(358.0f / 3.0f, 353.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 1.0f; damage = 10.0f;
		break;
	default:
		break;
	}
}

void Enermy::setPosition(Vector2f startPos, int type)
{
	this->type = type;
	body.setPosition(startPos);
	hitBlock.setPosition(startPos.x + 30.0f, startPos.y + 20.0f);
}