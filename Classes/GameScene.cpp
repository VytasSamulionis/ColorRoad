#include "GameScene.h"
#include "Background.h"
#include "Ground.h"
#include "PlayerCube.h"

using namespace cocos2d;

GameScene::GameScene()
	: Scene()
	, _background(nullptr)
	, _ground(nullptr)
	, _player(nullptr)
	, _isGameOver(false)
	, _score(0.0f)
	, _gameOverLabel(nullptr)
{

}

GameScene::~GameScene()
{
	delete _ground;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Director* director = Director::getInstance();
	Size size = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	_background = Background::create();
	addChild(_background, -10);

	_ground = new Ground(*this);

	_player = PlayerCube::create();
	_player->setAnchorPoint(Vec2::ZERO);
	_player->setPosition(Vec2(size.width * 0.3f, _ground->getMinSegmentSize().height * 2.0f));
	addChild(_player);

	_gameOverLabel = Label::createWithTTF("Game Over", "fonts/arial.ttf", 20);
	_gameOverLabel->setPosition(origin + size * 0.5f);
	addChild(_gameOverLabel);
	_gameOverLabel->setVisible(false);
	_continueLabel = Label::createWithTTF("press 'space' to continue...", "fonts/arial.ttf", 12);
	_continueLabel->setPosition(origin + size * 0.5f + Vec2(0.0f, -40.0f));
	addChild(_continueLabel);
	_continueLabel->setVisible(false);

	EventListenerKeyboard* inputListener = EventListenerKeyboard::create();
	inputListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(inputListener, _player);

	scheduleUpdate();

	return true;
}

void GameScene::update(float deltaTime)
{
	if (!_isGameOver)
	{
		_score += deltaTime;
	}
	_ground->update(deltaTime);
	_background->update(deltaTime, _ground->getSpeed());
	if (!_player->isJumping() && !_isGameOver)
	{
		Color playerColor = _player->getActiveColor();
		Color groundColor = _ground->getColorAtPosition(_player->getCubePositionX());
		if (playerColor != groundColor)
		{
			_player->damage(39.0f * deltaTime);
			if (_player->isDead())
			{
				_isGameOver = true;
				_gameOverLabel->setVisible(true);
				Director* director = Director::getInstance();
				Size size = director->getVisibleSize();
				Vec2 origin = director->getVisibleOrigin();
				char text[100];
				sprintf(text, "Your score: %d", (int)_score);
				_scoreLabel = Label::createWithTTF(text, "fonts/arial.ttf", 16);
				_scoreLabel->setPosition(origin + size * 0.5f + Vec2(0.0f, -20.0f));
				addChild(_scoreLabel);
				_continueLabel->setVisible(true);
			}
		}
		else
		{
			_player->heal(20.0f * deltaTime);
		}
	}
}

void GameScene::restart()
{
	_isGameOver = false;
	_gameOverLabel->setVisible(false);
	_continueLabel->setVisible(false);
	if (_scoreLabel)
	{
		_scoreLabel->removeFromParent();
		_scoreLabel = nullptr;
	}
	_score = 0.0f;
	_ground->reset();
	if (_player->getActiveColor() == Color::COLOR_YELLOW)
	{
		_player->switchSide(PlayerCube::SIDE_RIGHT);
	}
	_player->heal(MAX_HEALTH);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (_isGameOver)
	{
		if (EventKeyboard::KeyCode::KEY_SPACE == keyCode)
		{
			restart();
		}
		return;
	}
	PlayerCube* player = dynamic_cast<PlayerCube*>(event->getCurrentTarget());
	if (player)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			player->switchSide(PlayerCube::SIDE_LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			player->switchSide(PlayerCube::SIDE_TOP);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			player->switchSide(PlayerCube::SIDE_RIGHT);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			player->switchSide(PlayerCube::SIDE_BOTTOM);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			player->jump();
			break;
		}
	}
}
