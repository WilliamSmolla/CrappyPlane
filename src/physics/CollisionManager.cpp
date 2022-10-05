#include "pch.h"
#include "CollisionManager.h"
#include "maths/Maths.h"
#include "scene/Components.h"
#include "core/Log.h"

void CollisionManager::init()
{
}

void CollisionManager::integrate(entt::registry& registry, GameObject& player)
{   
    _isColliding = false;
    auto view = registry.view<Tag, Transform, SpriteRenderer, Collider>();
    
    Vec2 playerPosition = player.GetComponent<Transform>().position;
    SDL_Rect& playerSprite = player.GetComponent<SpriteRenderer>().sprite.GetTextureRect();
    
    for (auto& gameObject : view)
    {
        auto& tag = view.get<Tag>(gameObject).tag;
        auto& position = view.get<Transform>(gameObject).position;
        auto& sprite = view.get<SpriteRenderer>(gameObject).sprite.GetTextureRect();

        if (tag == "obstacle")
        {
            if (playerPosition.x + playerSprite.w / 8 >= position.x &&
                playerPosition.x + playerSprite.w / 8 <= position.x + sprite.w &&
                playerPosition.y + playerSprite.h / 2 >= position.y &&
                playerPosition.y + playerSprite.h / 2 <= position.y + sprite.h)
            {
                _isColliding = true;
            }            
        }   
    }
}
