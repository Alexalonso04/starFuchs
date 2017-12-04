#pragma once

#include "cocos2d.h"

class WelcomeScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void changeScene(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); //changes to the game scene

	CREATE_FUNC(WelcomeScene);
};