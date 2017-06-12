#include "Ground.h"

using namespace cocos2d;

Ground::Ground(Scene& scene)
	: _groundSkin(scene, "textures/gravel_rounded_top_left.png", "textures/gravel.png", "textures/gravel_rounded_top_right.png")
	, _speed(10.0f)
	, _acceleration(2.0f)
	, _playerPositionX(0.0f)
{
	for (int i = 0; i < MAX_GROUND_SEGMENTS; ++i)
	{
		_groundSegments[i].init(1, 1, _groundSkin);
	}
	reset();
}

Ground::~Ground()
{

}

void Ground::reset()
{
	float minGroundSegmentWidth = _groundSkin.getBody()->getContentSize().width * 2.0f;
	for (int i = 0; i < MAX_GROUND_SEGMENTS; ++i)
	{
		_groundSegments[i].setPositionX(i * minGroundSegmentWidth);
		_groundSegments[i].setHasLeftNeighbour(true);
		_groundSegments[i].setHasRightNeighbour(true);
		_groundSegments[i].setColor(Color::COLOR_GREEN);
	}
	_lastSegmentIndex = MAX_GROUND_SEGMENTS - 1;
	_speed = 10.0f;
}

void Ground::update(float deltaTime)
{
	for (int i = 0; i < MAX_GROUND_SEGMENTS; ++i)
	{
		_groundSegments[i].setPositionX(_groundSegments[i].getPositionX() - _speed * deltaTime);
	}
	for (int i = 0; i < MAX_GROUND_SEGMENTS; ++i)
	{
		if (_groundSegments[i].getPositionX() < -_groundSegments[i].getWidth())
		{
			repositionSegment(_groundSegments[i]);
			_lastSegmentIndex = i;
		}
	}
	_speed += _acceleration * deltaTime;
}

Color Ground::getColorAtPosition(float position)
{
	for (int i = 0; i < MAX_GROUND_SEGMENTS; ++i)
	{
		if (position >= _groundSegments[i].getPositionX() && position < _groundSegments[i].getPositionX() + _groundSegments[i].getWidth())
		{
			return _groundSegments[i].getColor();
		}
	}
	return Color::COLOR_NONE;
}

Size Ground::getMinSegmentSize() const
{
	Texture2D* body = _groundSkin.getBody();
	return body->getContentSize();
}

void Ground::repositionSegment(GroundSegment& segment)
{
	float newPosition = _groundSegments[_lastSegmentIndex].getPositionX() + _groundSegments[_lastSegmentIndex].getWidth();
	segment.resize(1, 1);
	int color = RandomHelper::random_int<int>(1, 2);
	segment.setColor((Color)color);
	segment.setPositionX(newPosition);
}

float Ground::getGapSize(float gapPositionX) const
{
	float travelDistance = gapPositionX - _playerPositionX;
	//float 
	return 0.0f;
}
