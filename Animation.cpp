#include "Animation.h"

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width  = texture->getSize().x / int(imageCount.x);
	uvRect.height = texture->getSize().y / int(imageCount.y);
}

Animation::~Animation() 
{
}

void Animation::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.width = abs(uvRect.width); 
}

void Animation::UpdateSize(Texture* texture)
{
	uvRect.width = texture->getSize().x / int(imageCount.x);
	uvRect.height = texture->getSize().y / int(imageCount.y);
}
