#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <sstream>
#include "Animation.h"
#include "Collider.h"
#include "Enermy.h"
#include "itemSlot.h"

using namespace sf;
using namespace std;

class Player
{
public:
	Player(Texture* texture, Vector2u imageCount, float switchTime,float speed, Vector2f pos);
	~Player();

	void Update(float deltaTime,Vector2f view,bool shoot);
	void Draw(RenderWindow& window);
	void Rotate(Vector2f mousePosView);
	void UpdateTex(Texture* texture, int type);
	void setPosition(Vector2f pos);
	void Reset();

	float hp, Armor, fireRate, damage;
	int kill, Ammo1, Ammo2, Ammo3,ammoType;
	int mag1, mag2, mag3, otherType;

	Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(hitBlock); }
	float GetDegree() { return rotation; } 
	int getRow() { return row; }
	int getType() { return type; }
	int getDamage() { return (int)damage; }

private:
	RectangleShape body, HPbar, BgHp, hitBlock,armor,BGarmor;
	Animation animation;
	unsigned int row;
	float speed;
	Vector2f mousePosView;
	Vector2f bodyPos;
	float rotation;
	int type;
};

