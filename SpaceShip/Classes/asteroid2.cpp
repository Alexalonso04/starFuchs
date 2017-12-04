#include "asteroid2.h"
#include "definitions.h"

USING_NS_CC;

asteroid2::asteroid2() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}



void  asteroid2::SpawnAsteroid(cocos2d::Layer *Layer) 
{
	CCLOG("SPAWN ASTEROID");

		auto aster = Sprite::create("Asteroid2.png");   //RIGHT NAME OF SPRITE??
		auto random = CCRANDOM_0_1();

		auto asterPosition = (random * visibleSize.width) + (aster->getContentSize().height );

		auto asterBody = PhysicsBody::createCircle(aster->getContentSize().width * 6/10);
		asterBody->setDynamic(false);
		asterBody->setCollisionBitmask(ASTEROID_COLLISION_BITMASK);
		asterBody->setContactTestBitmask(true);
		aster->setPhysicsBody(asterBody);

		aster->setPosition(Point(visibleSize.width / 2 + CCRANDOM_MINUS1_1() * 450, visibleSize.height + aster->getContentSize( ).height ));

		Layer->addChild(aster);

		auto asterAction = MoveBy::create(.005*visibleSize.height, Point(0, -visibleSize.height*1.5));

		aster->runAction(
			Sequence::create(
			(asterAction),
				RemoveSelf::create(true),
				nullptr));

} 
