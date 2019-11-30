#include "Player.h"

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed,Vector2f pos) :
	animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	row = 0;

	hp = 100.0f;
	kill = 0;
	type = 12;
	fireRate = 1.0f;
	damage = 0.0f;
	Armor = 0; Ammo1 = 20; Ammo2 = 0; Ammo3 = 0;
	otherType = 12;
	mag1 = 0; mag2 = 0; mag3 = 0; ammoType = 1;
	rotation = 0;

	body.setSize(Vector2f(329.0f / 3.0f, 300.0f / 3.0f)); 
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(pos);
	body.setTexture(texture);

	hitBlock.setSize(Vector2f(45.0f, 45.0f));
	hitBlock.setOrigin(hitBlock.getSize() / 2.0f);
	hitBlock.setOutlineThickness(2.0f);
	hitBlock.setPosition(1280.0f + 30.0f, 640.0f + 20.0f);
	hitBlock.setOutlineColor(Color::Black);
	hitBlock.setFillColor(Color::Transparent);

	HPbar.setFillColor(Color::Color(255, 0, 0,255));
	BgHp.setFillColor(Color::Blue);
	BgHp.setOutlineThickness(2.0f);
	BgHp.setOutlineColor(Color::Black);
}

Player::~Player()
{
}

void Player::Update(float deltaTime, Vector2f view, bool shoot)
{
	Vector2f movement(0.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if(body.getPosition().x >=60.0f) movement.x -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (body.getPosition().x <= 3940.0f) movement.x += speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (body.getPosition().y >= 60.0f) movement.y -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		if (body.getPosition().y <= 3940.0f) movement.y += speed;
	}

	if (movement.x == 0.0f && movement.y == 0.0f) { row = 0; }
	else { row = 1; }

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	hitBlock.move(movement * deltaTime);
	body.setPosition(hitBlock.getPosition());
}

void Player::Draw(RenderWindow& window) {
	window.draw(body);
	//window.draw(hitBlock);
}

void Player::Rotate(Vector2f mousePosView) {
	bodyPos = body.getPosition();
	const double PI = 3.14159265;
	float dx = mousePosView.x - bodyPos.x;
	float dy = mousePosView.y - bodyPos.y;
	rotation = (atan2(dy, dx)) * 180 / PI;
	
	if (Keyboard::isKeyPressed(Keyboard::Key::C)) {
		cout << "MousePosition : " << mousePosView.x << " " << mousePosView.y << endl;
		cout << "PlayerPosition : " << bodyPos.x << " " << bodyPos.y << endl;
		cout << "Degree : " << rotation << endl;
		
	}
	body.setRotation(rotation);
}

void Player::UpdateTex(Texture* texture,int type)
{
	switch (type)
	{
	case 0: //Piston
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(291.0f / 3.0f, 256.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.5f; damage = 5.0f;
		this->type = type;
		if(otherType!=type) mag1 = 20;
		ammoType = 1;
		break;
	case 1: //Piston
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(291.0f / 3.0f, 256.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.5f; damage = 5.0f;
		this->type = type;
		if (otherType != type) mag1 = 20;
		ammoType = 1;
		break;
	case 2: //Piston
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(291.0f / 3.0f, 256.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.5f; damage = 5.0f;
		this->type = type;
		if (otherType != type) mag1 = 20;
		ammoType = 1;
		break;
	case 3: //Gloza
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(313.0f / 3.0f, 207.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.075f; damage = 6.0f;
		this->type = type;
		if (otherType != type) mag2 = 40;
		ammoType = 2;
		break;
	case 4: //Thomson
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(313.0f / 3.0f, 207.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.1f; damage = 10.0f;
		this->type = type;
		if (otherType != type) mag2 = 40;
		ammoType = 2;
		break;
	case 5: //AKM
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(313.0f / 3.0f, 207.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 0.15f; damage = 15.0f;
		this->type = type;
		if (otherType != type) mag2 = 40;
		ammoType = 2;
		break;
	case 6: //ShotGun
		body.setTexture(texture);
		animation.UpdateSize(texture);
		body.setSize(Vector2f(358.0f / 3.0f, 353.0f / 3.0f));
		body.setOrigin(body.getSize() / 2.0f);
		fireRate = 1.0f; damage = 15.0f;
		this->type = type;
		if (otherType != type) mag3 = 5;
		ammoType = 3;
		break;
	case 7: //Bandage
		hp += 40;
		if (hp > 100) hp = 100;
		break;
	case 8: //Armor
		Armor += 50;
		if (Armor > 100) Armor = 100;
		break;
	case 9: //Ammo 5.5
		Ammo1 += 40;
		break;
	case 10: //Ammo 7.2
		Ammo2 += 80;
		break;
	case 11: //Ammo Shotgun
		Ammo3 += 10;
		break;
	default:
		break;
	}
}

void Player::setPosition(Vector2f pos)
{
	hitBlock.setPosition(pos);
	body.setPosition(hitBlock.getPosition());
}

void Player::Reset()
{
	hp = 100.0f;
	kill = 0;
	type = 12;
	fireRate = 1.0f;
	damage = 0.0f;
	Armor = 0; Ammo1 = 20; Ammo2 = 0; Ammo3 = 0;
	otherType = 12;
	mag1 = 0; mag2 = 0; mag3 = 0; ammoType = 1;
	rotation = 0;
}
