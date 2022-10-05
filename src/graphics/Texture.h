#pragma once
#include <SDL.h>
#include <SDL_image.h>

// TODO: Refactor this class to include spritesheet ?

class Texture
{
public:
	Texture() = default;
	Texture(std::string id, SDL_Texture* texture, int numberOfFrames);
	~Texture();

	std::string GetID() const;
	SDL_Texture* GetNativeTexture() const;
	SDL_Rect& GetTextureRect() const;

	int GetNumberOfFrames() const;
	void SetNumberOfFrames(int nbFrames);

private:
	std::string m_ID; 
	SDL_Texture* m_Texture;
	SDL_Rect* m_TextureRect;
	int m_NbFrames;
};

