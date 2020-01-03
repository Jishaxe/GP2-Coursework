#include "Audio.h"

void Audio::init()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Failed to init SDL_mixer" << std::endl;
	}

	Mix_AllocateChannels(16);
}

void Audio::loadSound(string filename, string audioname)
{
	Mix_Chunk* soundClip = NULL;
	soundClip = Mix_LoadWAV(filename.c_str());

	if (soundClip == NULL) {
		cout << "Failed to load sound clip " << audioname.c_str() << " from  " << filename.c_str() << " - " << Mix_GetError() << endl;
		return;
	}

	sounds.insert(make_pair(audioname, soundClip));
}

void Audio::playSound(string audioname) {
	auto sound = sounds.find(audioname);
	if (sound == sounds.end()) {
		cout << "Tried to play audio clip " << audioname.c_str() << " but it doesn't exist" << endl;
		return;
	}

	Mix_Chunk* clip = sound->second;
	
	if (Mix_PlayChannel(-1, clip, 0) == -1) cout << "Failed to play audio clip " << audioname.c_str() << " - " << Mix_GetError() << endl;
}