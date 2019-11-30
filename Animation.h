#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation
{
public:
	Animation(Texture* texture, Vector2u imageCount,float switchTime);
	~Animation();

	void Update(int row, float deltaTime);
	void UpdateSize(Texture* texture);
	IntRect uvRect;

private:
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;
};

