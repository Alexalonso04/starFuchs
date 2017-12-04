#pragma once

#include "cocos2d.h"

class OverScene: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(unsigned int tempScore);
	virtual bool init();
	void changeScene(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(OverScene);
};