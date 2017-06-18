#pragma once

#include "cocos2d.h"
#include "Color.h"

#define MAX_HEALTH 100.0f

class PlayerCube : public cocos2d::Node
{
public:
	enum CubeSide
	{
		SIDE_LEFT,
		SIDE_TOP,
		SIDE_RIGHT,
		SIDE_BOTTOM
	};

	virtual bool init() override;

	void jump();
	void switchSide(CubeSide side);
	float getCubePositionX() const;
	float getCubeHeight() const;
	float getCubeWidth() const;
	Color getActiveColor() const;
	void damage(float power);
	void heal(float power);

	inline float getHealth() const { return _health; }
	inline bool isDead() const { return _health <= 0.0f; }
	inline bool isJumping() const { return _isJumping; }
	inline bool hasLanded() const { return _hasLanded; }
	inline void setLandingProcessed() { _hasLanded = false; }

	CREATE_FUNC(PlayerCube);

protected:
	PlayerCube();
	virtual ~PlayerCube();

	void updateHealthIndicator();

private:
	cocos2d::Sprite* _cube;
	cocos2d::Sprite* _healthIndicator;
	float _health;
	bool _isJumping;
	bool _hasLanded;
};
