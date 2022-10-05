#pragma once
#include <SDL_ttf.h>
#include <SDL_FontCache.h>
#include "../src/scene/Scene.h"
#include "scene/GameObject.h"
#include "utils/Timer.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void HandleEvents(const SDL_Event& event) override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void ResetGame();
	void ResetGameForMenu();
	void LoadGameFromMenu();
	void HandlePlayerMovements(float deltaTime);
	void HandleWorldMovements();
	void HandleGameSpeed();
	void HandleEndGame();
	void RenderScore();
	void RenderMenu();

private:

	int score = 0;
	int alpha = 0;

	float backgroundSpeed = 1.0f;
	float obstacleSpeed = 1.5f;
	Timer speedTimer;
	FC_Font* font;
	FC_Font* titleFont;
	bool _isPlaying = false;
	bool _isMenu = true;
	bool _gameOver = false;
	bool _isLoading = true;
	GameObject _player;
	GameObject _background;
	GameObject _grass;
	GameObject _rockUpOne;
	GameObject _rockUpTwo;
	GameObject _rockDownOne;
	GameObject _rockDownTwo;
	Timer _fadeOutTimer;
	GameObject _blackCanvas;
};

