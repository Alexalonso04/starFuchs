#include "asteroid.h"
#include "definitions.h"

USING_NS_CC;

asteroid::asteroid() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	speed = 0.005;
}



void  asteroid::SpawnAsteroid(cocos2d::Layer *Layer) 
{
	CCLOG("SPAWN ASTEROID");
		auto aster = Sprite::create("Asteroid2.png");   //RIGHT NAME OF SPRITE??
		auto random = CCRANDOM_0_1();

		auto asterPosition = (random * visibleSize.width) + (aster->getContentSize().height );

		auto asterBody = PhysicsBody::createCircle(aster->getContentSize().width * 6/10);
		//asterBody->setDynamic(false);
		asterBody->setGravityEnable(false);
		asterBody->setCollisionBitmask(ASTEROID_COLLISION_BITMASK);
		asterBody->setContactTestBitmask(true);
		aster->setPhysicsBody(asterBody);

		aster->setPosition(Point(visibleSize.width / 2 + CCRANDOM_MINUS1_1() * 450, visibleSize.height + aster->getContentSize( ).height ));

		Layer->addChild(aster);

		auto asterAction = MoveBy::create(speed*visibleSize.height, Point(0, -visibleSize.height*1.5));

		aster->runAction(
			Sequence::create(
			(asterAction),
				RemoveSelf::create(true),
				nullptr));

		Point point1 = aster->convertToNodeSpace(aster->getPosition());

		if (point1.y < visibleSize.height / 2)
		{
			aster->removeChild(aster, true);
		}

} 

void asteroid::changeSpeed() {
	speed = speed / 1.01;
}
