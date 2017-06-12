#include "GroundSegment.h"
#include "GroundSegmentSkin.h"

using namespace cocos2d;

GroundSegment::GroundSegment()
	: _hasLeftNeighbour(false)
	, _leftCorner(nullptr)
	, _leftCornerPosition(0.0f)
	, _hasRightNeighbour(false)
	, _rightCorner(nullptr)
	, _rightCornerPosition(0.0f)
	, _top(nullptr)
	, _topPosition(0.0f)
	, _bottom(nullptr)
	, _bottomPosition(0.0f)
	, _width(0)
	, _height(0)
	, _skin(nullptr)
{
}

GroundSegment::~GroundSegment()
{
	if (_top)
	{
		_top->release();
	}
}

void GroundSegment::init(int width, int height, const GroundSegmentSkin& skin)
{
	_skin = &skin;
	Size size = _skin->getBody()->getContentSize();
	_leftCorner = Sprite::createWithTexture(_skin->getLeftCorner());
	_leftCorner->setAnchorPoint(Vec2::ZERO);
	_skin->getLeftCornerBatch()->addChild(_leftCorner, -2);
	_rightCorner = Sprite::createWithTexture(_skin->getRightCorner());
	_rightCorner->setAnchorPoint(Vec2::ZERO);
	_skin->getRightCornerBatch()->addChild(_rightCorner, -1);
	_top = Sprite::createWithTexture(_skin->getBody());
	_top->setAnchorPoint(Vec2::ZERO);
	_top->setPosition(Vec2(size.width, 0.0f));
	_top->setStretchEnabled(false);
	_top->retain();
	_bottom = Sprite::createWithTexture(_skin->getBody());
	_bottom->setAnchorPoint(Vec2::ZERO);
	_bottom->setStretchEnabled(false);
	_skin->getBodyBatch()->addChild(_bottom, 1);
	resize(width, height);
}

void GroundSegment::setPositionX(float positionX)
{
	_leftCorner->setPositionX(positionX + _leftCornerPosition);
	_rightCorner->setPositionX(positionX + _rightCornerPosition);
	_top->setPositionX(positionX + _topPosition);
	_bottom->setPositionX(positionX + _bottomPosition);
	_positionX = positionX;
}

float GroundSegment::getWidth() const
{
	return _width * 2.0f * _skin->getBody()->getContentSize().width;
}

void GroundSegment::resize(int width, int height)
{
	if ((width == _width && height == _height) || width == 0 || height == 0)
	{
		return;
	}
	Size size = _skin->getBody()->getContentSize();
	if (width == 1)
	{
		_top->removeFromParent();
	}
	else 
	{
		if (!_top->getParent())
		{
			_skin->getBodyBatch()->addChild(_top, 0);
		}
		_top->setContentSize(Size((width * 2 - 2) * size.width, size.height));
		_top->setTextureRect(Rect(Vec2::ZERO, _top->getContentSize()));
	}
	float topY = (height * 2 - 1) * size.height;
	_leftCornerPosition = 0.0f;
	_leftCorner->setPosition(Vec2(_positionX + _leftCornerPosition, topY));
	_topPosition = size.width;
	_top->setPosition(Vec2(_positionX + _topPosition, topY));
	_rightCornerPosition = (width * 2 - 1) * size.width;
	_rightCorner->setPosition(Vec2(_positionX + _rightCornerPosition, topY));
	_bottom->setContentSize(Size(width * 2 * size.width, topY));
	_bottom->setTextureRect(Rect(Vec2::ZERO, _bottom->getContentSize()));
	_bottomPosition = 0.0f;
	_bottom->setPositionX(_positionX);
	_width = width;
	_height = height;
}

void GroundSegment::setColor(Color color)
{
	Color3B spriteColor = Color3B::WHITE;
	switch (color)
	{
		case Color::COLOR_GREEN:
			spriteColor = Color3B(24, 148, 7);
			break;
		case Color::COLOR_YELLOW:
			spriteColor = Color3B(212, 229, 22);
			break;
		default:
			CCASSERT(false, "Invalid color");
			break;
	}
	_leftCorner->setColor(spriteColor);
	_top->setColor(spriteColor);
	_rightCorner->setColor(spriteColor);
	_bottom->setColor(spriteColor);
	_color = color;
}

void GroundSegment::setHasLeftNeighbour(bool hasLeftNeighbour)
{
	if (hasLeftNeighbour != _hasLeftNeighbour)
	{
		_leftCorner->removeFromParent();
		if (hasLeftNeighbour)
		{
			_leftCorner->setTexture(_skin->getBody());
			_skin->getBodyBatch()->addChild(_leftCorner);
		}
		else
		{	
			_leftCorner->setTexture(_skin->getLeftCorner());
			_skin->getLeftCornerBatch()->addChild(_leftCorner);
		}
		_hasLeftNeighbour = hasLeftNeighbour;
	}
}

void GroundSegment::setHasRightNeighbour(bool hasRightNeighbour)
{
	if (hasRightNeighbour != _hasRightNeighbour)
	{
		_rightCorner->removeFromParent();
		if (hasRightNeighbour)
		{
			_rightCorner->setTexture(_skin->getBody());
			_skin->getBodyBatch()->addChild(_rightCorner);
		}
		else
		{
			_rightCorner->setTexture(_skin->getRightCorner());
			_skin->getRightCornerBatch()->addChild(_rightCorner);
		}
		_hasRightNeighbour = hasRightNeighbour;
	}
}
