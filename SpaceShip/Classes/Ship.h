#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"

class Ship
{
public:
	Ship(cocos2d::Layer *layer);
	
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite * ship;

};

#endif // __SHIP_H__
