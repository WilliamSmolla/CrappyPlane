#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_FontCache.h>
#include "../graphics/Texture.h"
#include "../graphics/Renderer.h"
#include "../scene/GameObject.h"

class AssetManager
{
public:
	static AssetManager& GetInstance()
	{
		static AssetManager instance;
		return instance;
	}

	AssetManager(AssetManager const&) = delete;
	void operator=(AssetManager const&) = delete;

	static void Init() { GetInstance().init(); }
	static void LoadTexture(const char* filepath) { GetInstance().loadTexture(filepath); }
	static void LoadSound(const char* filepath) { GetInstance().loadSound(filepath); }
	static void LoadMusic(const char* filepath) { GetInstance().loadMusic(filepath); }

	static Texture& GetTexture(std::string name) { return GetInstance().getTexture(name); }
	static Mix_Chunk& GetSound(std::string name) { return GetInstance().getSound(name); }
	static Mix_Music& GetMusic(std::string name) { return GetInstance().getMusic(name); }

private:
	AssetManager(){}

	std::string getNameFromFile(const char* filepath);

	void init();

	void loadTexture(const char* filepath);
	void loadSound(const char* filepath);
	void loadMusic(const char* filepath);

	Texture& getTexture(std::string name);
	Mix_Chunk& getSound(std::string name);
	Mix_Music& getMusic(std::string name);

	std::map<std::string, Texture*> m_TextureBank;
	std::map<std::string, Mix_Chunk*> m_SoundBank;
	std::map<std::string, Mix_Music*> m_MusicBank;
};

