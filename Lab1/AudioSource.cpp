#include "AudioSource.h"

ComponentType AudioSource::getType()
{
	return AUDIO_SOURCE;
}

void AudioSource::init()
{
}

void AudioSource::setAudio(Audio * audio)
{
	this->audio = audio;
}

void AudioSource::update(double deltaTime, InputData input)
{
}

void AudioSource::draw(Camera * camera)
{
}

void AudioSource::play(string audioname)
{
	audio->playSound(audioname);
}
