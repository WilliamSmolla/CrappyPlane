#include "pch.h"
#include "AssetManager.h"
#include "Log.h"

void AssetManager::loadTexture(const char* filepath)
{   
    SDL_Surface* surface = IMG_Load(filepath);
    std::string filename = getNameFromFile(filepath);
    m_TextureBank[filename] = new Texture(filename,
        SDL_CreateTextureFromSurface(Renderer::GetInstance().GetNativeRenderer(), surface), 1);

    SDL_FreeSurface(surface);
}

void AssetManager::loadSound(const char* filepath)
{
    std::string filename = getNameFromFile(filepath);
    m_SoundBank[filename] = Mix_LoadWAV(filepath);
    if (m_SoundBank[filename] == NULL)
    {
        Log::LogCritical("Unable to load sound: " + std::string(Mix_GetError()));
    }
}

void AssetManager::loadMusic(const char* filepath)
{   
    std::string filename = getNameFromFile(filepath);
    m_MusicBank[filename] = Mix_LoadMUS(filepath);

    if (m_MusicBank[filename] == NULL)
    {
        Log::LogCritical("Unable to load music: " + std::string(Mix_GetError()));
    }
}

Texture& AssetManager::getTexture(std::string name)
{
    return *m_TextureBank[name];
}

Mix_Chunk& AssetManager::getSound(std::string name)
{
    return *m_SoundBank[name];
}

Mix_Music& AssetManager::getMusic(std::string name)
{
    return *m_MusicBank[name];
}

std::string AssetManager::getNameFromFile(const char* filepath)
{
    std::string filename = std::string(filepath);
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }

    const size_t period_idx = filename.rfind('.');
    if (std::string::npos != period_idx)
    {
        filename.erase(period_idx);
    }

    return filename;
}

void AssetManager::init()
{
    // asset loading
    // sprites
    LoadTexture("res/background.png");
    LoadTexture("res/player.png");
    LoadTexture("res/groundGrass.png");
    LoadTexture("res/rockGrass.png");
    LoadTexture("res/rockGrassDown.png");
    LoadTexture("res/explosion.png");
    LoadTexture("res/canvas.png");
    // music
    LoadMusic("res/MainTheme.ogg");
    // sfx
    LoadSound("res/explosion.mp3");
}

