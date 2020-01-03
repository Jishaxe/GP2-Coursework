#pragma once
#include "Component.h"
#include "Audio.h"

class AudioSource :
	public Component
{
private:
	Audio* audio;
public:
	ComponentType getType();
	void init();
	void setAudio(Audio* audio);
	void update(double deltaTime, InputData input);
	void draw(Camera* camera);
	void play(string audioname);
};

