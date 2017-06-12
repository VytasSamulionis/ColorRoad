#pragma once

#include "cocos2d.h"
#include "Color.h"

class GroundSegmentSkin;

class GroundSegment
{
public:
	GroundSegment();
	~GroundSegment();

	void init(int width, int height, const GroundSegmentSkin& skin);

	void setPositionX(float positionX);
	inline float getPositionX() const { return _positionX; }
	float getWidth() const;
	void resize(int width, int height);
	void setColor(Color color);
	inline Color getColor() const { return _color; }
	void setHasLeftNeighbour(bool hasLeftNeighbour);
	void setHasRightNeighbour(bool hasRightNeighbour);

private:
	bool _hasLeftNeighbour;
	cocos2d::Sprite* _leftCorner;
	float _leftCornerPosition;
	bool _hasRightNeighbour;
	cocos2d::Sprite* _rightCorner;
	float _rightCornerPosition;
	cocos2d::Sprite* _top;
	float _topPosition;
	cocos2d::Sprite* _bottom;
	float _bottomPosition;
	int _width;
	int _height;
	float _positionX;
	Color _color;

	const GroundSegmentSkin* _skin;
};
