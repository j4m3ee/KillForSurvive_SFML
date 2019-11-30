#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <sstream>
#include "Animation.h"
#include "Collider.h"
#include "Player.h"
#include "Enermy.h"
//#include "Bullet.h"

using namespace sf;
using namespace std;

class Enermy
{
public:
	Enermy(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	~Enermy();

	void Update(float deltaTime, Vector2f playerPos,float range,bool saw);
	void Draw(RenderWindow& window);
	void setPosition(Vector2f startPos, int type);
	void UpdateTex(Texture* texture);
	int getType() { return type; }

	float hp,damage,fireRate;
	bool shoot = false,resetTime = false;

	Vector2f playerCenter, aimDir;
	
	Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(hitBlock); }

private:
	Clock clock;
	RectangleShape body, HPbar, BgHp, hitBlock;
	Animation animation;
	unsigned int row;
	float speed,Time;
	Vector2f playerPos;
	Vector2f bodyPos;
	int drt,dist,cout,type;
	/*Bullet b1;
	vector<Bullet> bullets;
	Vector2f BullplayerCenter, BullaimDir;*/
	
};

