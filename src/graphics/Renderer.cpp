#include "pch.h"
#include "Renderer.h"
#include "../core/Log.h"
#include "core/Window.h"
#include "../scene/Components.h"

Renderer::Renderer()
{
    m_Renderer = SDL_CreateRenderer(Window::GetInstance().GetNativeWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr) {
        Log::LogCritical("Failed to create Renderer.");
        exit(EXIT_FAILURE);
    }
    else 
    {
        Log::LogInfo("Renderer created successfully.");
    }

    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
}

void Renderer::init()
{  
}

void Renderer::render(entt::registry& registry)
{
    auto view = registry.view<Tag, Transform, SpriteRenderer>();

    // sort gameObjects by layer for rendering
    registry.sort<Tag>([](const auto& lhs, const auto& rhs) {

        return lhs.layer < rhs.layer;
    });

    for (auto& gameObject : view)
    {
        auto& position = view.get<Transform>(gameObject).position;
        auto& spriteRenderer = view.get<SpriteRenderer>(gameObject);
        auto& layer = view.get<Tag>(gameObject).layer;
        auto& timer = view.get<SpriteRenderer>(gameObject).timer;

        if (spriteRenderer.isAnimated)
        {
            if (!spriteRenderer.isLooping)
            {
                if (!timer.IsStarted())
                {
                    timer.Start();
                }
                SDL_Rect sourceQuad = SDL_Rect{ 0, 0, spriteRenderer.sprite.GetTextureRect().w / spriteRenderer.numberOfFrames,
                spriteRenderer.sprite.GetTextureRect().h };

                sourceQuad.x = sourceQuad.w * static_cast<int>((SDL_GetTicks() /
                    spriteRenderer.timeBetweenFrames) % spriteRenderer.numberOfFrames);

                SDL_Rect renderQuad = SDL_Rect{ (int)position.x, (int)position.y,
                    spriteRenderer.sprite.GetTextureRect().w / spriteRenderer.numberOfFrames,
                    spriteRenderer.sprite.GetTextureRect().h };

                if (debug)
                {
                    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(m_Renderer, &renderQuad);
                }

                if (timer.GetTime() >= spriteRenderer.numberOfFrames * spriteRenderer.timeBetweenFrames)
                {
                    if (debug)
                    {
                        SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
                        SDL_RenderFillRect(m_Renderer, &renderQuad);
                    }

                    timer.Pause();
                }
                else
                {
                    if (debug)
                    {
                        SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
                        SDL_RenderFillRect(m_Renderer, &renderQuad);
                    }

                    SDL_RenderCopy(Renderer::GetInstance().GetNativeRenderer(), spriteRenderer.sprite.GetNativeTexture(),
                        &sourceQuad, &renderQuad);
                }
            }
            else
            {
                SDL_Rect sourceQuad = SDL_Rect{ 0, 0, spriteRenderer.sprite.GetTextureRect().w / spriteRenderer.numberOfFrames,
                spriteRenderer.sprite.GetTextureRect().h };

                sourceQuad.x = sourceQuad.w * static_cast<int>((SDL_GetTicks() /
                    spriteRenderer.timeBetweenFrames) % spriteRenderer.numberOfFrames);

                SDL_Rect renderQuad = SDL_Rect{ (int)position.x, (int)position.y,
                    spriteRenderer.sprite.GetTextureRect().w / spriteRenderer.numberOfFrames,
                    spriteRenderer.sprite.GetTextureRect().h };

                if (debug)
                {
                    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(m_Renderer, &renderQuad);
                }

                SDL_RenderCopy(Renderer::GetInstance().GetNativeRenderer(), spriteRenderer.sprite.GetNativeTexture(),
                    &sourceQuad, &renderQuad);
            }                                                               
        }
        else
        {
            if (debug)
            {
                SDL_Rect renderQuad = SDL_Rect{ (int)position.x, (int)position.y,
                spriteRenderer.sprite.GetTextureRect().w, spriteRenderer.sprite.GetTextureRect().h };

                SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(m_Renderer, &renderQuad);
            }
            SDL_Rect renderQuad = SDL_Rect{ (int)position.x, (int)position.y,
                spriteRenderer.sprite.GetTextureRect().w, spriteRenderer.sprite.GetTextureRect().h };
        
            SDL_RenderCopy(m_Renderer, spriteRenderer.sprite.GetNativeTexture(),
                &spriteRenderer.sprite.GetTextureRect(), &renderQuad);
        } 
    }
}

SDL_Renderer* Renderer::getNativeRenderer()
{
	return m_Renderer;
}

void Renderer::renderClear(Vec4 color)
{
    SDL_SetRenderDrawColor(m_Renderer, color.x, color.y, color.z, color.w);
    SDL_RenderClear(m_Renderer);   
}

void Renderer::renderPresent()
{
    SDL_RenderPresent(m_Renderer);
}





