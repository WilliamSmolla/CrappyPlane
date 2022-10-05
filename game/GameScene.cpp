#include "pch.h"
#include "GameScene.h"
#include "core/AssetManager.h"
#include "physics/CollisionManager.h"
#include "../src/core/SoundManager.h"
#include "core/Log.h"
#include "scene/Components.h"

GameScene::GameScene()
	: Scene{}
{
	SoundManager::PlayMusic("MainTheme", MixOption::REPEAT);
	SoundManager::PauseMusic();

	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

	// player creation
	GameObject player = CreateGameObject();
	_player = player;

	player.AddComponent<Tag>();
	player.AddComponent<Transform>();
	player.AddComponent<SpriteRenderer>();
	player.AddComponent<Movement>();

	player.GetComponent<Tag>().tag = "player";
	player.GetComponent<Tag>().layer = 5;
	player.GetComponent<Transform>().position = Vec2(100, 100);
	player.GetComponent<SpriteRenderer>().isAnimated = true;
	player.GetComponent<SpriteRenderer>().numberOfFrames = 4;
	player.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("player");
	player.GetComponent<SpriteRenderer>().timeBetweenFrames = 100;
	player.GetComponent<SpriteRenderer>().isLooping = true;

	player.GetComponent<Movement>().acceleration.y = 1000;

	// background creation
	GameObject background = CreateGameObject();
	_background = background;


	background.AddComponent<Tag>();
	background.AddComponent<Transform>();
	background.AddComponent<SpriteRenderer>();

	background.GetComponent<Tag>().tag = "background";
	background.GetComponent<Tag>().layer = 1;
	background.GetComponent<Transform>().position = Vec2(0, 0);
	background.GetComponent<SpriteRenderer>().isAnimated = false;
	background.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("background");

	// ground creation
	GameObject grass = CreateGameObject();
	_grass = grass;

	grass.AddComponent<Tag>();
	grass.AddComponent<Transform>();
	grass.AddComponent<SpriteRenderer>();
	grass.AddComponent<Collider>();

	grass.GetComponent<Tag>().tag = "obstacle";
	grass.GetComponent<Tag>().layer = 2;
	grass.GetComponent<Transform>().position = Vec2(0.0f, 410.0f);
	grass.GetComponent<SpriteRenderer>().isAnimated = false;
	grass.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("groundGrass");

	GameObject rockUpOne = CreateGameObject();
	_rockUpOne = rockUpOne;

	rockUpOne.AddComponent<Tag>();
	rockUpOne.AddComponent<Transform>();
	rockUpOne.AddComponent<SpriteRenderer>();
	rockUpOne.AddComponent<Collider>();

	rockUpOne.GetComponent<Tag>().tag = "obstacle";
	rockUpOne.GetComponent<Tag>().layer = 2;
	rockUpOne.GetComponent<Transform>().position = Vec2(800, 0);
	rockUpOne.GetComponent<SpriteRenderer>().isAnimated = false;
	rockUpOne.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("rockGrassDown");

	GameObject rockUpTwo = CreateGameObject();
	_rockUpTwo = rockUpTwo;

	rockUpTwo.AddComponent<Tag>();
	rockUpTwo.AddComponent<Transform>();
	rockUpTwo.AddComponent<SpriteRenderer>();
	rockUpTwo.AddComponent<Collider>();

	rockUpTwo.GetComponent<Tag>().tag = "obstacle";
	rockUpTwo.GetComponent<Tag>().layer = 2;
	rockUpTwo.GetComponent<Transform>().position = Vec2(1300, 0);
	rockUpTwo.GetComponent<SpriteRenderer>().isAnimated = false;
	rockUpTwo.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("rockGrassDown");

	GameObject rockDownOne = CreateGameObject();
	_rockDownOne = rockDownOne;

	rockDownOne.AddComponent<Tag>();
	rockDownOne.AddComponent<Transform>();
	rockDownOne.AddComponent<SpriteRenderer>();
	rockDownOne.AddComponent<Collider>();

	rockDownOne.GetComponent<Tag>().tag = "obstacle";
	rockDownOne.GetComponent<Tag>().layer = 3;
	rockDownOne.GetComponent<Transform>().position = Vec2(1100, 480 - 239);
	rockDownOne.GetComponent<SpriteRenderer>().isAnimated = false;
	rockDownOne.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("rockGrass");

	GameObject rockDownTwo = CreateGameObject();
	_rockDownTwo = rockDownTwo;

	rockDownTwo.AddComponent<Tag>();
	rockDownTwo.AddComponent<Transform>();
	rockDownTwo.AddComponent<SpriteRenderer>();
	rockDownTwo.AddComponent<Collider>();

	rockDownTwo.GetComponent<Tag>().tag = "obstacle";
	rockDownTwo.GetComponent<Tag>().layer = 3;
	rockDownTwo.GetComponent<Transform>().position = Vec2(1500, 480 - 239);
	rockDownTwo.GetComponent<SpriteRenderer>().isAnimated = false;
	rockDownTwo.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("rockGrass");

	// canvas creation

	GameObject canvas = CreateGameObject();
	_blackCanvas = canvas;

	canvas.AddComponent<Tag>();
	canvas.AddComponent<Transform>();
	canvas.AddComponent<SpriteRenderer>();

	canvas.GetComponent<Tag>().tag = "canvas";
	canvas.GetComponent<Tag>().layer = 6;
	canvas.GetComponent<Transform>().position = Vec2(0, 0);
	canvas.GetComponent<SpriteRenderer>().isAnimated = false;
	canvas.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("canvas");

	SDL_SetTextureBlendMode(canvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(canvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), 0);

	font = FC_CreateFont();
	titleFont = FC_CreateFont();
	FC_LoadFont(font, Renderer::GetNativeRenderer(), "res/blackmud.ttf", 20, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
	FC_LoadFont(titleFont, Renderer::GetNativeRenderer(), "res/blackmud.ttf", 37, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
}

GameScene::~GameScene()
{
}

void GameScene::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (_isMenu)
			{
				_isPlaying = true;
			}
			else
			{
				_player.GetComponent<Movement>().velocity.y = -400.0f;
			}
			break;

		case SDLK_d:
			Renderer::GetInstance().debug = true;
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			break;

		case SDLK_d:
			Renderer::GetInstance().debug = false;
			break;
		}
	}
}

void GameScene::Update(float deltaTime)
{	
	if (!_isMenu)
	{
		SoundManager::ResumeMusic();

		if (_isLoading)
		{
			ResetGame();
		}
		else
		{
			HandleWorldMovements();
			HandlePlayerMovements(deltaTime);
			HandleGameSpeed();

			CollisionManager::Integrate(_registry, _player);

			HandleEndGame();
		}	
	}
	else
	{
		SoundManager::PlayMusic("MainTheme", MixOption::REPEAT);
		SoundManager::PauseMusic();
		if (_isLoading)
		{
			ResetGameForMenu();
		}
		else
		{
			LoadGameFromMenu();
		}
	}
}

void GameScene::Render()
{
	Renderer::Render(_registry);

	if (!_isMenu)
	{
		RenderScore();
	}
	else
	{
		RenderMenu();
	}
}

void GameScene::ResetGame()
{
	_player.GetComponent<Transform>().position = Vec2(250, 100);
	_background.GetComponent<Transform>().position = Vec2(0, 0);
	_grass.GetComponent<Transform>().position = Vec2(0.0f, 410.0f);
	_rockUpOne.GetComponent<Transform>().position = Vec2(800, 0);
	_rockUpTwo.GetComponent<Transform>().position = Vec2(1300, 0);
	_rockDownOne.GetComponent<Transform>().position = Vec2(1100, 480 - 239);
	_rockDownTwo.GetComponent<Transform>().position = Vec2(1500, 480 - 239);

	_player.GetComponent<SpriteRenderer>().isAnimated = true;
	_player.GetComponent<SpriteRenderer>().numberOfFrames = 4;
	_player.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("player");
	_player.GetComponent<SpriteRenderer>().timeBetweenFrames = 100;
	_player.GetComponent<SpriteRenderer>().isLooping = true;

	score = 0;

	backgroundSpeed = 1.0f;
	obstacleSpeed = 1.5f;

	if (!_fadeOutTimer.IsStarted())
	{
		_fadeOutTimer.Start();
	}

	int fadeTimer = _fadeOutTimer.GetTime() / 4;

	SDL_SetTextureBlendMode(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), -fadeTimer);

	if (fadeTimer >= 250)
	{
		fadeTimer = 0;
		_fadeOutTimer.Stop();
		_isLoading = false;
		_isMenu = false;
		_gameOver = false;
		_player.GetComponent<SpriteRenderer>().timer.Stop();
		return;
	}
}

void GameScene::ResetGameForMenu()
{
	_player.GetComponent<Transform>().position = Vec2(800, 100);
	_background.GetComponent<Transform>().position = Vec2(0, 0);
	_grass.GetComponent<Transform>().position = Vec2(800, 410.0f);
	_rockUpOne.GetComponent<Transform>().position = Vec2(800, 0);
	_rockUpTwo.GetComponent<Transform>().position = Vec2(1300, 0);
	_rockDownOne.GetComponent<Transform>().position = Vec2(1100, 480 - 239);
	_rockDownTwo.GetComponent<Transform>().position = Vec2(1500, 480 - 239);

	if (!_fadeOutTimer.IsStarted())
	{
		_fadeOutTimer.Start();
	}

	int fadeTimer = _fadeOutTimer.GetTime() / 4;

	SDL_SetTextureBlendMode(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), -fadeTimer);

	if (fadeTimer >= 250)
	{
		fadeTimer = 0;
		_fadeOutTimer.Stop();
		_isLoading = false;
	}
}

void GameScene::LoadGameFromMenu()
{
	if (_isPlaying)
	{
		if (!_fadeOutTimer.IsStarted())
		{
			_fadeOutTimer.Start();
		}

		int fadeTimer = _fadeOutTimer.GetTime() / 4;

		SDL_SetTextureBlendMode(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), fadeTimer);

		if (_fadeOutTimer.GetTime() >= 1000)
		{
			_fadeOutTimer.Stop();

			_isMenu = false;
			_isLoading = true;
			_isPlaying = false;
			return;
		}
	}
}

void GameScene::HandlePlayerMovements(float deltaTime)
{
	float playerYVel = _player.GetComponent<Movement>().velocity.y;
	float playerYAcc = _player.GetComponent<Movement>().acceleration.y;
	float palyerYPos = _player.GetComponent<Transform>().position.y;

	if (playerYVel >= 300)
	{
		_player.GetComponent<Movement>().velocity.y = 300;
	}

	if (palyerYPos < 0)
	{
		_player.GetComponent<Movement>().velocity.y = -playerYVel;
		_player.GetComponent<Transform>().position.y = 0;
	}
	else if (palyerYPos + _player.GetComponent<SpriteRenderer>().sprite.GetTextureRect().h > 480)
	{
		_player.GetComponent<Movement>().velocity.y = -playerYVel;
		_player.GetComponent<Transform>().position.y = 480 - _player.GetComponent<SpriteRenderer>().sprite.GetTextureRect().h;
	}

	_player.GetComponent<Movement>().velocity.y += _player.GetComponent<Movement>().acceleration.y * deltaTime / 1000.0f;
	_player.GetComponent<Transform>().position.y += _player.GetComponent<Movement>().velocity.y * deltaTime / 1000.0f;
}

void GameScene::HandleWorldMovements()
{
	float backgroundXPos = _background.GetComponent<Transform>().position.x;
	float backgroundWidth = _background.GetComponent<SpriteRenderer>().sprite.GetTextureRect().w;

	float groundXpos = _grass.GetComponent<Transform>().position.x;
	float groundWidth = _grass.GetComponent<SpriteRenderer>().sprite.GetTextureRect().w;

	float obstDownOneXpos = _rockUpOne.GetComponent<Transform>().position.x;
	float obstDownOneWidth = _rockUpOne.GetComponent<SpriteRenderer>().sprite.GetTextureRect().w;

	float obstDownTwoXpos = _rockUpTwo.GetComponent<Transform>().position.x;
	float obstDownTwoWidth = _rockUpTwo.GetComponent<SpriteRenderer>().sprite.GetTextureRect().w;

	float obstUpOneXpos = _rockDownOne.GetComponent<Transform>().position.x;
	float obstUpOneWidth = _rockDownOne.GetComponent<SpriteRenderer>().sprite.GetTextureRect().w;

	float obstUpTwoXpos = _rockDownTwo.GetComponent<Transform>().position.x;
	float obstUpTwoWidth = _rockDownTwo.GetComponent<SpriteRenderer>().sprite.GetTextureRect().w;

	if (backgroundXPos < -(backgroundWidth / 2))
	{
		_background.GetComponent<Transform>().position.x = 0;
	}

	if (groundXpos < -(groundWidth / 2))
	{
		_grass.GetComponent<Transform>().position.x = 0;
	}

	if (obstDownOneXpos < -obstDownOneWidth)
	{
		_rockUpOne.GetComponent<Transform>().position = Vec2(800, Random::Range(-100, 0));
		score++;
	}

	if (obstDownTwoXpos < -obstDownTwoWidth)
	{
		_rockUpTwo.GetComponent<Transform>().position = Vec2(800, Random::Range(-100, 0));
		score++;
	}

	if (obstUpOneXpos < -obstUpOneWidth)
	{
		_rockDownOne.GetComponent<Transform>().position = Vec2(800, Random::Range(480 - 239, 480 - 139));
		score++;
	}

	if (obstUpTwoXpos < -obstUpTwoWidth)
	{
		_rockDownTwo.GetComponent<Transform>().position = Vec2(800, Random::Range(480 - 239, 480 - 139));
		score++;
	}

	if (!_gameOver)
	{
		_background.GetComponent<Transform>().position.x -= backgroundSpeed;

		_grass.GetComponent<Transform>().position.x -= obstacleSpeed;
		_rockUpOne.GetComponent<Transform>().position.x -= obstacleSpeed;
		_rockUpTwo.GetComponent<Transform>().position.x -= obstacleSpeed;
		_rockDownOne.GetComponent<Transform>().position.x -= obstacleSpeed;
		_rockDownTwo.GetComponent<Transform>().position.x -= obstacleSpeed;
	}
}

void GameScene::HandleGameSpeed()
{
	if (!speedTimer.IsStarted())
	{
		speedTimer.Start();
	}

	if (speedTimer.GetTime() >= 10000)
	{
		speedTimer.Stop();

		backgroundSpeed += 0.1f;
		obstacleSpeed += 0.1f;

		speedTimer.Start();
	}
}

void GameScene::HandleEndGame()
{
	if (CollisionManager::IsColliding())
	{
		SoundManager::StopMusic();
		SoundManager::PlaySFX("explosion", 0, MixOption::NO_REPEAT);
		speedTimer.Stop();
		_gameOver = true;
		_player.GetComponent<SpriteRenderer>().sprite = AssetManager::GetTexture("explosion");
		_player.GetComponent<SpriteRenderer>().numberOfFrames = 7;
		_player.GetComponent<SpriteRenderer>().isLooping = false;
	}

	// when explosion sprite finish it's animation.
	if (_player.GetComponent<SpriteRenderer>().timer.IsPaused())
	{
		//Log::LogTrace("ready to fade out and load main menu");
		if (!_fadeOutTimer.IsStarted())
		{
			_fadeOutTimer.Start();
		}

		int fadeTimer = _fadeOutTimer.GetTime() / 4;

		SDL_SetTextureBlendMode(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_blackCanvas.GetComponent<SpriteRenderer>().sprite.GetNativeTexture(), fadeTimer);

		if (_fadeOutTimer.GetTime() >= 1000)
		{
			_fadeOutTimer.Stop();

			_isMenu = true;
			_isLoading = true;
			return;
		}
	}
}

void GameScene::RenderScore()
{
	std::string scoreT = "Score: ";
	std::string scoreText = std::to_string(score);
	std::string finalScore = scoreT + scoreText;

	FC_Rect messageRect;
	messageRect.w = 200;
	messageRect.h = 200;
	messageRect.x = 0;
	messageRect.y = 25;
	FC_DrawBoxAlign(font, Renderer::GetNativeRenderer(), messageRect, FC_ALIGN_CENTER, scoreT.c_str());
	FC_DrawBoxAlign(font, Renderer::GetNativeRenderer(), messageRect, FC_ALIGN_RIGHT, scoreText.c_str());
}

void GameScene::RenderMenu()
{
	FC_Rect messageRect;
	messageRect.w = 500;
	messageRect.h = 300;
	messageRect.x = 150;
	messageRect.y = 100;

	FC_DrawBoxAlign(titleFont, Renderer::GetNativeRenderer(), messageRect, FC_ALIGN_CENTER, "Crappy Plane");

	FC_Rect playRect;
	playRect.w = 300;
	playRect.h = 300;
	playRect.x = 250;
	playRect.y = 300;

	FC_DrawBoxAlign(font, Renderer::GetNativeRenderer(), playRect, FC_ALIGN_CENTER, "Press SPACE to play");
}



