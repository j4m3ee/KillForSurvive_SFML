#include "Item.h"

Item::Item(Texture* texture)
{
	body.setTexture(texture);
	body.setSize(Vector2f(90, 48));
	body.setOrigin(body.getSize() / 2.0f);

	hitBlock.setSize(Vector2f(50, 50));
	hitBlock.setOrigin(hitBlock.getSize() / 2.0f);
	hitBlock.setOutlineThickness(2.0f);
	hitBlock.setOutlineColor(Color::Black);
	hitBlock.setFillColor(Color::Transparent);
}

Item::~Item()
{
}

void Item::Draw(RenderWindow& window)
{
	window.draw(body);
	//window.draw(hitBlock);
}

void Item::setPosition(Vector2f Pos,int Type)
{
	body.setPosition(Pos);
	hitBlock.setPosition(body.getPosition());
	type = Type;
	switch (Type) {
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
	case 7:
		uvRect = IntRect(120, 64 * 2, 120, 64);
		break;
	case 8:
		uvRect = IntRect(240, 64 * 2, 120, 64);
		break;
	case 9:
		uvRect = IntRect(0, 64 * 3, 120, 64);
		break;
	case 10:
		uvRect = IntRect(120, 64 * 3, 120, 64);
		break;
	case 11:
		uvRect = IntRect(240, 64 * 3, 120, 64);
		break;
	}
	body.setTextureRect(uvRect);
}
