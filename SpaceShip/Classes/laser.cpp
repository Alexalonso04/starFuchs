#include "laser.h"
#include "definitions.h"


USING_NS_CC;

laser::laser() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}



void  laser::SpawnLaser(cocos2d::Layer *Layer)
{
	CCLOG("SPAWN LASER");

	auto las = Sprite::create("laser.png");   //RIGHT NAME OF SPRITE??

	auto lasBody = PhysicsBody::createBox(las->getContentSize());

	auto lasPosition = (visibleSize.width/2);

	lasBody->setDynamic(false);

	las->setPhysicsBody(lasBody);
	
	las->setPosition(visibleSize.width / 2, 100);  //the position should be linked with the position of the ship 

	Layer->addChild(las);

	auto lasAction = MoveBy::create(.005*visibleSize.height, Point(0, visibleSize.height*1.5));

	las->runAction(lasAction);

}
