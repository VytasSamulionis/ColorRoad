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
	, _gameOverCooldown(2.0f)
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

	_ground->setPlayerPositionX(_player->getCubePositionX());
	_ground->setPlayerSizeX(_player->getCubeWidth());

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
	if (_isGameOver)
	{
		_gameOverCooldown -= deltaTime;
		if (_gameOverCooldown < 0.0f)
		{
			_gameOverCooldown = 0.0f;
			_continueLabel->setVisible(true);
		}
	}
	else if (!_player->isJumping())
	{
		Color playerColor = _player->getActiveColor();
		Color groundColor = _ground->getColorAtPosition(_player->getCubePositionX());
		if (groundColor == Color::COLOR_NONE)
		{
			_player->damage(MAX_HEALTH);
			_player->setLandingProcessed();
			_player->runAction(MoveBy::create(0.5f, Vec2(-_ground->getSpeed() * 0.5, -(_ground->getMinSegmentSize().height * 2.0f + _player->getCubeHeight()))));
		}
		if (playerColor != groundColor)
		{
			if (_player->hasLanded())
			{
				_player->damage(MAX_HEALTH * 0.5f);
				_player->setLandingProcessed();
			}
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
			}
		}
		else
		{
			_player->heal(20.0f * deltaTime);
			_player->setLandingProcessed();
		}
	}
}

void GameScene::restart()
{
	_isGameOver = false;
	_gameOverLabel->setVisible(false);
	_continueLabel->setVisible(false);
	_gameOverCooldown = 2.0f;
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
	_player->stopAllActions();
	_player->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.3f, _ground->getMinSegmentSize().height * 2.0f));
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (_isGameOver)
	{
		if (EventKeyboard::KeyCode::KEY_SPACE == keyCode && _gameOverCooldown <= 0.0f)
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
