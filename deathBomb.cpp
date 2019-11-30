#include "deathBomb.h"

deathBomb::deathBomb(Texture* texture, Vector2u imageCount, float switchTime)
{
	done = false;
	effect.setSize(Vector2f(200, 200));
	effect.setTexture(texture);
	effect.setTextureRect(IntRect(0, 0, 100, 100));
	effect.setOrigin(effect.getSize() / 2.0f);
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;
	row = 0;

	uvRect.width = texture->getSize().x / int(imageCount.x);
	uvRect.height = texture->getSize().y / int(imageCount.y);
}

deathBomb::~deathBomb()
{
}

void deathBomb::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.y ++;
			currentImage.x = 0;
		}

		if (currentImage.y >= imageCount.y) {
			done = true;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.width = abs(uvRect.width);

	effect.setTextureRect(uvRect);
}

void deathBomb::UpdateSize(Texture* texture)
{
	uvRect.width = texture->getSize().x / int(imageCount.x);
	uvRect.height = texture->getSize().y / int(imageCount.y);
}

void deathBomb::setPosition(Vector2f pos)
{
	effect.setPosition(pos);
}

void deathBomb::Draw(RenderWindow& window)
{
	if(done == false) window.draw(effect);
}
