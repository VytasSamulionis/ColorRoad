#pragma once

#include "cocos2d.h"
#include "GroundSegmentSkin.h"
#include "GroundSegment.h"
#include "Color.h"

#define MAX_GROUND_SEGMENTS 10

class Ground
{
public:
	Ground(cocos2d::Scene& scene);
	~Ground();

	inline void setPlayerPositionX(float position) { _playerPositionX = position; }
	inline void setPlayerSizeX(float size) { _playerSizeX = size; }

	void reset();
	void update(float deltaTime);
	Color getColorAtPosition(float position);
	cocos2d::Size getMinSegmentSize() const;
	inline float getSpeed() const { return _speed; }
private:
	void repositionSegment(GroundSegment& segment);
	float getGapSize(float gapPositionX) const;
private:
	GroundSegmentSkin _groundSkin;
	GroundSegment _groundSegments[MAX_GROUND_SEGMENTS];
	int _lastSegmentIndex;
	float _speed;
	float _acceleration;
	float _playerPositionX;
	float _playerSizeX;
	float _gapSize;
};
