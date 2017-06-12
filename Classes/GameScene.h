#pragma once

#include "cocos2d.h"

class Background;
class Ground;
class PlayerCube;

class GameScene : public cocos2d::Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool init() override;
	virtual void update(float deltaTime) override;
	void restart();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(GameScene);
private:
	Background* _background;
	Ground* _ground;
	PlayerCube* _player;
	bool _isGameOver;
	float _score;
	cocos2d::Label* _gameOverLabel;
	cocos2d::Label* _scoreLabel;
	cocos2d::Label* _continueLabel;
};
