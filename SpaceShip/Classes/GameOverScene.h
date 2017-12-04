#pragma once

#include "cocos2d.h"

class OverScene: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(unsigned int tempScore); //constructor for the game scene
	virtual bool init(); //function to intialize game settings
	void changeScene(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); //function to change to the next scene based on key pressed

	CREATE_FUNC(OverScene);
};