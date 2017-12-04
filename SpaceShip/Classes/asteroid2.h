#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"

class asteroid2 {
public:
	asteroid2();

	void SpawnAsteroid(cocos2d::Layer * Layer);

	

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
		
	cocos2d::Sprite *aster;

};

#endif