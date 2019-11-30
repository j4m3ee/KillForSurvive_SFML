#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class Effect
{
public:
	Effect(Sound* sound, float volume, float time);
	~Effect();
private:
	SoundBuffer soundBuffer;
};

