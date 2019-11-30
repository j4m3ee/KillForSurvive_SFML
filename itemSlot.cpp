#include "itemSlot.h"

itemSlot::itemSlot(Texture* texture)
{
	slot1.setTexture(texture), slot2.setTexture(texture);
	slot1.setSize(Vector2f(120, 64));
	slot2.setSize(Vector2f(120, 64));
	selector1.setOutlineThickness(2.0f);
	selector1.setOutlineColor(Color(50, 50, 50,255));
	selector1.setSize(Vector2f(130, 64));
	selector2.setOutlineThickness(2.0f);
	selector2.setOutlineColor(Color(50, 50, 50, 255));
	selector2.setSize(Vector2f(120, 64));
	ammoSelector.setOutlineThickness(2.0f);
	ammoSelector.setOutlineColor(Color(50, 50, 50, 255));
	ammoSelector.setSize(Vector2f(70, 27));
	ammoSelector.setOrigin(ammoSelector.getSize() / 2.0f);
	selector1.setFillColor(Color(51, 255, 51, 255));
	selector2.setFillColor(Color(51, 255, 51, 255));
	ammoSelector.setFillColor(Color(102, 255, 255, 255));
	s1 = false; s2 = false; nowSlot = 1;

}

itemSlot::~itemSlot()
{
}

void itemSlot::Draw(RenderWindow& window)
{
	switch (nowSlot)
	{
	case 1:
		window.draw(selector1);
		break;
	case 2:
		window.draw(selector2);
		break;
	default:
		break;
	}
	window.draw(slot1);
	window.draw(slot2);
	if (s2 == false) window.draw(selector2);
	window.draw(ammoSelector);
}

void itemSlot::updateSlot(int type)
{
	this->type = type;
	if (type <= 6) {
		switch (type) {
		case 0:
			uvRect = IntRect(0, 0, 120, 64);
			break;
		case 1:
			uvRect = IntRect(120, 0, 120, 64);
			break;
		case 2:
			uvRect = IntRect(240, 0, 120, 64);
			break;
		case 3:
			uvRect = IntRect(0, 64, 120, 64);
			break;
		case 4:
			uvRect = IntRect(120, 64, 120, 64);
			break;
		case 5:
			uvRect = IntRect(240, 64, 120, 64);
			break;
		case 6:
			uvRect = IntRect(0, 64 * 2, 120, 64);
			break;
		}

		if (s1 == false) {
			slot1.setTextureRect(uvRect);
			s1 = true; slotType1 = type;
			nowSlot = 1;
		}
		else if (s2 == false) {
			slot2.setTextureRect(uvRect);
			s2 = true; slotType2 = type;
			nowSlot = 2;
		}
		else {
			switch (nowSlot)
			{
			case 1:
				slot1.setTextureRect(uvRect);
				s1 = true; slotType1 = type;
				break;
			case 2:
				slot2.setTextureRect(uvRect);
				s2 = true; slotType2 = type;
				break;
			default:
				break;
			}
		}
	}
}

void itemSlot::Update(Vector2f pos, int ammoType)
{
	slot1.setPosition(pos.x + 630, pos.y + 425);
	slot2.setPosition(pos.x + 770, pos.y + 425);
	selector1.setPosition(pos.x + 630, pos.y + 425);
	selector2.setPosition(pos.x + 770, pos.y + 425);

	switch (ammoType)
	{
	case 1:
		ammoSelector.setPosition(pos.x + 670, pos.y + 515);
		break;
	case 2:
		ammoSelector.setPosition(pos.x + 770, pos.y + 515);
		break;
	case 3:
		ammoSelector.setPosition(pos.x + 840, pos.y + 515);
		break;
	default:
		break;
	}
}

void itemSlot::reStart()
{
	s1 = false; s2 = false; nowSlot = 1;
	uvRect = IntRect(0, 0, 120, 64);
	slot1.setTextureRect(uvRect);
	slotType1 = 0;
	slot2.setTextureRect(uvRect);
	slotType2 = 0;
}
