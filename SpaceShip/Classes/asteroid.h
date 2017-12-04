#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"

class asteroid {
public:
	asteroid();

	void SpawnAsteroid(cocos2d::Layer * Layer);
	void changeSpeed(); //function to change the speed at which the asteroid falls
	

private:
	cocos2d::Size visibleSize; //holds the visible size of the screen
	cocos2d::Vec2 origin; //holds the origin of the screen
	double speed; //holds the speed at which the asteroid falls
		
	cocos2d::Sprite *aster; //holds an asteroid object
};

#endif