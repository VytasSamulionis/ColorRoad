#include "PlayerCube.h"

using namespace cocos2d;

bool PlayerCube::init()
{
	if (!Node::init())
	{
		return false;
	}
	_cube = Sprite::createWithSpriteFrameName("player.png");
	Size size = _cube->getContentSize();
	_cube->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
	addChild(_cube, -1);
	_health = MAX_HEALTH;
	_healthIndicator = Sprite::createWithSpriteFrameName("health.png");
	_healthIndicator->setAnchorPoint(Vec2(0.5f, 0.0f));
	_healthIndicator->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f - _healthIndicator->getContentSize().height * 0.5f));
	_healthIndicator->setScaleY(0.0f);
	addChild(_healthIndicator, 1);
	return true;
}

void PlayerCube::jump()
{
	if (!_isJumping)
	{
		_isJumping = true;
		auto jump = JumpBy::create(1.0f, Vec2::ZERO, 60.0f, 1);
		auto callback = CallFunc::create([&]() {
			_isJumping = false;
			_hasLanded = true;
		});
		_cube->runAction(Sequence::createWithTwoActions(jump, callback));
		_healthIndicator->runAction(jump->clone());
	}
}

void PlayerCube::switchSide(CubeSide side)
{
	float deltaAngle = 0.0f;
	switch (side)
	{
		case SIDE_LEFT:
			deltaAngle = -90.0f;
			break;
		case SIDE_RIGHT:
			deltaAngle = 90.0f;
			break;
		case SIDE_TOP:
			deltaAngle = 180.0f;
			break;
		case SIDE_BOTTOM:
			deltaAngle = 0.0f;
			break;
	}
	if (deltaAngle != 0.0f)
	{
		_healthIndicator->setVisible(false);
		auto rotate = RotateBy::create(0.1f, deltaAngle);
		auto callback = CallFunc::create([&]() {
			_healthIndicator->setVisible(true);
		});
		_cube->runAction(Sequence::createWithTwoActions(rotate, callback));
	}
}

float PlayerCube::getCubePositionX() const
{
	return getPositionX() + _cube->getContentSize().width * 0.5f;
}

float PlayerCube::getCubeHeight() const
{
	return _cube->getContentSize().height;
}

float PlayerCube::getCubeWidth() const
{
	return _cube->getContentSize().width;
}

Color PlayerCube::getActiveColor() const
{
	float angle = _cube->getRotation();
	while (angle < 0.0f)
	{
		angle += 360.0f;
	}
	while (angle > 360.0f)
	{
		angle -= 360.0f;
	}
	if (angle > 225 && angle <= 315 || angle > 45 && angle <= 135)
	{
		return Color::COLOR_YELLOW;
	}
	return Color::COLOR_GREEN;
}

void PlayerCube::damage(float power)
{
	_health -= power;
	if (_health < 0.0f)
	{
		_health = 0.0f;
	}
	updateHealthIndicator();
}

void PlayerCube::heal(float power)
{
	_health += power;
	if (_health > MAX_HEALTH)
	{
		_health = MAX_HEALTH;
	}
	updateHealthIndicator();
}

PlayerCube::PlayerCube()
	: Node()
	, _cube(nullptr)
	, _healthIndicator(nullptr)
	, _health(MAX_HEALTH)
	, _isJumping(false)
	, _hasLanded(false)
{
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("textures/sprites.plist");
}

PlayerCube::~PlayerCube()
{
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->removeSpriteFramesFromFile("textures/sprites.plist");
}

void PlayerCube::updateHealthIndicator()
{
	float healthPercentage = _health / MAX_HEALTH;
	_healthIndicator->setScaleY(1.0f - healthPercentage);
}