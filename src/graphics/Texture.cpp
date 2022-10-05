#include "pch.h"
#include "Texture.h"

Texture::Texture(std::string id, SDL_Texture* texture, int numberOfFrames)
	: m_ID{ id }, m_Texture{ texture }, m_NbFrames{ numberOfFrames }
{
	m_TextureRect = new SDL_Rect();
	SDL_QueryTexture(texture, NULL, NULL, &m_TextureRect->w, &m_TextureRect->h);
	m_TextureRect->x = 0;
	m_TextureRect->y = 0;
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_Texture);
	delete m_TextureRect;
}

std::string Texture::GetID() const
{
	return m_ID;
}

SDL_Texture* Texture::GetNativeTexture() const
{
	return m_Texture;
}

SDL_Rect& Texture::GetTextureRect() const
{
	return *m_TextureRect;
}

int Texture::GetNumberOfFrames() const
{
	return m_NbFrames;
}

void Texture::SetNumberOfFrames(int nbFrames)
{
	m_NbFrames = nbFrames;
}

