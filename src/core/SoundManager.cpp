#include "pch.h"
#include "SoundManager.h"
#include "Log.h"

void SoundManager::init()
{
}

void SoundManager::playSFX(std::string name, int channel, MixOption option)
{
	Mix_PlayChannel(channel, &AssetManager::GetSound(name), (int)option);
}

void SoundManager::playMusic(std::string name, MixOption option)
{
	Mix_PlayMusic(&AssetManager::GetMusic(name), (int)option);
}

void SoundManager::pauseMusic()
{
	Mix_PauseMusic();
}

void SoundManager::stopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::setChannelVolume(int channel, int volume)
{
	Mix_Volume(channel, volume);
}

void SoundManager::setMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void SoundManager::resumeMusic()
{
	Mix_ResumeMusic();
}
