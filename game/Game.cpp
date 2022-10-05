#include "pch.h"
#include "Game.h"


Game::Game()
{
	//unsigned int mainScene = SceneManager::AddScene(new MainMenu(_registry));
	//unsigned int gameScene = SceneManager::AddScene(new GameScene(_registry));
	_scene = std::make_unique<GameScene>();
}

Game::~Game() 
{
	
}

void Game::HandleEvents(const SDL_Event& event)
{
	_scene->HandleEvents(event);
}

void Game::Update(float deltaTime)
{
	_scene->Update(deltaTime);
}

void Game::Render()
{
	Renderer::RenderClear(Vec4(123, 167, 225, 255));

	_scene->Render();

	Renderer::RenderPresent();
}
