#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;

class dropPlane
{
public:
	dropPlane(Texture* planeTex,float speed);
	~dropPlane();
	void Update(float deltaTime, Vector2f view);
	void Draw(RenderWindow& window);
	void setPosition(Vector2f pos);

	Vector2f GetPosition() { return body.getPosition(); }

private:
	RectangleShape body;
	float speed;
};

