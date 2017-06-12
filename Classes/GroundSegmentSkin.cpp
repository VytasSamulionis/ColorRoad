#include "GroundSegmentSkin.h"

using namespace cocos2d;

GroundSegmentSkin::GroundSegmentSkin(Scene& scene, const std::string& leftCorner, const std::string& body, const std::string& rightCorner)
{
	TextureCache* textureCache = Director::getInstance()->getTextureCache();
	Texture2D::TexParams texParams = { GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT };
	_leftCorner = textureCache->addImage(leftCorner);
	_leftCorner->setTexParameters(texParams);
	_leftCornerBatch = SpriteBatchNode::createWithTexture(_leftCorner, 10);
	_leftCornerBatch->setAnchorPoint(Vec2::ZERO);
	scene.addChild(_leftCornerBatch, -1);
	_body = textureCache->addImage(body);
	_body->setTexParameters(texParams);
	_bodyBatch = SpriteBatchNode::createWithTexture(_body, 20);
	_bodyBatch->setAnchorPoint(Vec2::ZERO);
	scene.addChild(_bodyBatch, 0);
	_rightCorner = textureCache->addImage(rightCorner);
	_rightCorner->setTexParameters(texParams);
	_rightCornerBatch = SpriteBatchNode::createWithTexture(_rightCorner, 10);
	_rightCornerBatch->setAnchorPoint(Vec2::ZERO);
	scene.addChild(_rightCornerBatch, 1);
}

GroundSegmentSkin::~GroundSegmentSkin()
{
	TextureCache* textureCache = Director::getInstance()->getTextureCache();
	textureCache->removeTexture(_leftCorner);
	textureCache->removeTexture(_body);
	textureCache->removeTexture(_rightCorner);
}