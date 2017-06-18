#include "Background.h"

using namespace cocos2d;

bool Background::init()
{
	if (!Node::init())
	{
		return false;
	}
	Director* director = Director::getInstance();
	Size size = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();
	TextureCache* textureCache = director->getTextureCache();
	Texture2D::TexParams texParams = { GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT };
	Texture2D* backgroundTexture = textureCache->addImage("textures/background.png");
	backgroundTexture->setTexParameters(texParams);
	for (int i = 0; i < 2; ++i)
	{
		_backgrounds[i] = Sprite::createWithTexture(backgroundTexture, Rect(Vec2::ZERO, Size(size.width * 2.0f, size.height)));
		_backgrounds[i]->setAnchorPoint(Vec2::ZERO);
		_backgrounds[i]->setPosition(Vec2(origin.x + i * size.width * 2.0f, origin.y));
		_backgrounds[i]->setColor(Color3B(7, 107, 154));
		addChild(_backgrounds[i], -20 + i);
	}
	Color3B rowColor[3] = { Color3B(18, 111, 5), Color3B(12, 77, 4), Color3B(8, 51, 2) };
	Color3B rowAltColor[3] = { Color3B(142, 153, 15), Color3B(105, 113, 11), Color3B(71, 77, 7) };
	float rowHeight[3] = { 150.0f, 200.0f, 250.0f };
	float rowScale[3] = { 0.75f, 0.5f, 0.25f };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			_rows[i].buildings[j] = Sprite::create("textures/building.png");
			_rows[i].buildings[j]->setAnchorPoint(Vec2::ZERO);
			Color3B color = RandomHelper::random_int<int>(0, 1) == 0 ? rowColor[i] : rowAltColor[i];
			_rows[i].buildings[j]->setColor(color);
			float lastPosition = 0.0f;
			if (j > 0)
			{
				lastPosition = _rows[i].buildings[j - 1]->getPositionX() + _rows[i].buildings[j - 1]->getContentSize().width;
			}
			_rows[i].buildings[j]->setPosition(Vec2(lastPosition + rand_0_1() * size.width, rowHeight[i]));
			_rows[i].buildings[j]->setScale(rowScale[i]);
			addChild(_rows[i].buildings[j], i * -5 - j);
		}
		_rows[i].lastBuildingIndex = 4;
	}
    return true;
}

void Background::update(float deltaTime, float speed)
{
	float backgroundSpeed = speed / 4.0f;
	float rowSpeed[3] = { speed / 2.0f, speed / 2.5f, speed / 3.0f };
	for (int i = 0; i < 2; ++i)
	{
		_backgrounds[i]->setPositionX(_backgrounds[i]->getPositionX() - backgroundSpeed * deltaTime);
	}
	for (int i = 0; i < 2; ++i)
	{
		if (_backgrounds[i]->getPositionX() < -_backgrounds[i]->getContentSize().width)
		{
			_backgrounds[i]->setPositionX(_backgrounds[(i + 1) % 2]->getPositionX() + _backgrounds[(i + 1) % 2]->getContentSize().width);
		}
	}
	Size size = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			float newPositionX = _rows[i].buildings[j]->getPositionX() - rowSpeed[i] * deltaTime;
			_rows[i].buildings[j]->setPositionX(newPositionX);
			if (newPositionX < -_rows[i].buildings[j]->getContentSize().width)
			{
				Sprite* lastBuilding = _rows[i].buildings[_rows[i].lastBuildingIndex];
				float lastPosition = lastBuilding->getPositionX() + lastBuilding->getContentSize().width;
				float newPosition = lastPosition + rand_0_1() * size.width;
				if (newPosition < size.width)
				{
					newPosition = lastPosition + size.width;
				}
				_rows[i].buildings[j]->setPositionX(newPosition);
				_rows[i].lastBuildingIndex = j;
			}
		}
	}
}

Background::Background()
	: Node()
{

}

Background::~Background()
{

}
