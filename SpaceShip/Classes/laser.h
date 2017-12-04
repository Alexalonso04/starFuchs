#ifndef __LASER_H__
#define __LASER_H__
#include "cocos2d.h"

class laser {
public:
	laser();

	void  SpawnLaser(cocos2d::Layer *Layer);



private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *las;

};

#endif