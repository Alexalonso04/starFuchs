#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"

class asteroid {
public:
	asteroid();

	void SpawnAsteroid(cocos2d::Layer * Layer);
	void changeSpeed();
	

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	double speed;		
	cocos2d::Sprite *aster;

};

#endif