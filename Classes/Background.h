#pragma once

#include "cocos2d.h"

class Background : public cocos2d::Node
{
public:
	virtual bool init() override;
	void update(float deltaTime, float speed);

	CREATE_FUNC(Background);

protected:
	Background();
	virtual ~Background();

private:
	struct BuildingRow
	{
		cocos2d::Sprite* buildings[5];
		int lastBuildingIndex;
	};

	cocos2d::Sprite* _backgrounds[2];
	BuildingRow _rows[3];
};
