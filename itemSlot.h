#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Item.h"
#include "Player.h"

using namespace sf;
using namespace std;

class itemSlot
{
public:
	itemSlot(Texture* texture);
	~itemSlot();
	void Draw(RenderWindow& window);
	void updateSlot(int type);
	void Update(Vector2f pos, int ammoType);
	void reStart();
	bool s1, s2;
	int slotType1, slotType2,nowSlot;
	int getType() { return type; }
private:
	RectangleShape slot1, slot2, selector1, selector2,ammoSelector;
	IntRect uvRect;
	int type,ammoType;
};

