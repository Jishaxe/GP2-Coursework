#pragma once
#include <map>
#include <SDL/SDL_mixer.h>
#include <iostream>

using namespace std;

class Audio
{
public:
	void init();
	void loadSound(string filename, string audioname);
	void playSound(string audioname);
private:
	map<string, Mix_Chunk*> sounds;
};

