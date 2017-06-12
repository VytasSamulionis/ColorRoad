#pragma once

#include "cocos2d.h"

class GroundSegmentSkin
{
public:
	GroundSegmentSkin(cocos2d::Scene& scene, const std::string& leftCorner, const std::string& body, const std::string& rightCorner);
	~GroundSegmentSkin();

	inline cocos2d::Texture2D* getLeftCorner() const { return _leftCorner; }
	inline cocos2d::SpriteBatchNode* getLeftCornerBatch() const { return _leftCornerBatch; }
	inline cocos2d::Texture2D* getBody() const { return _body; }
	inline cocos2d::SpriteBatchNode* getBodyBatch() const { return _bodyBatch; }
	inline cocos2d::Texture2D* getRightCorner() const { return _rightCorner; }
	inline cocos2d::SpriteBatchNode* getRightCornerBatch() const { return _rightCornerBatch; }
private:
	cocos2d::Texture2D* _leftCorner;
	cocos2d::SpriteBatchNode* _leftCornerBatch;
	cocos2d::Texture2D* _body;
	cocos2d::SpriteBatchNode* _bodyBatch;
	cocos2d::Texture2D* _rightCorner;
	cocos2d::SpriteBatchNode* _rightCornerBatch;
};
