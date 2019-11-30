#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class deathBomb
{
public:
	deathBomb(Texture* texture, Vector2u imageCount, float switchTime);
	~deathBomb();
	void Update(float deltaTime);
	void UpdateSize(Texture* texture);
	void setPosition(Vector2f pos);
	void Draw(RenderWindow& window);
	IntRect uvRect;
	bool done;
private:
	RectangleShape effect;
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;
	int row;
};

