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
	CCLOG("SPAWN ASTEROID"); //logs to the console to make sure the asteroid has spawned

		auto aster = Sprite::create("Asteroid2.png");	//Creates an asteroid sprite
		auto random = CCRANDOM_0_1(); //variable to hold a random number between 0 and 1

		auto asterPosition = (random * visibleSize.width) + (aster->getContentSize().height ); //sets the position of the asteroid

		//Creates a physics body for the asteroid used in determining the collisions
		auto asterBody = PhysicsBody::createCircle(aster->getContentSize().width * 6/10);

		//asterBody->setDynamic(false);
		asterBody->setGravityEnable(false); //disables gravity for the asteroids 
		asterBody->setCollisionBitmask(ASTEROID_COLLISION_BITMASK); //sets a collision mask to compare collisions with other object
		asterBody->setContactTestBitmask(true);
		aster->setPhysicsBody(asterBody); //assigns a physics body to the sprite node

		//Gives the sprite a random position outside the visible screen
		aster->setPosition(Point(visibleSize.width / 2 + CCRANDOM_MINUS1_1() * 450, visibleSize.height + aster->getContentSize( ).height ));

		Layer->addChild(aster); //adds the asteroid sprite to the scene tree

		//Moves the asteroid at a specific rate
		auto asterAction = MoveBy::create(speed*visibleSize.height, Point(0, -visibleSize.height*1.5));

		//Spawn the asteroid and makes sure that it doesn't spawn on top of each other
		aster->runAction(
			Sequence::create(
			(asterAction),
				RemoveSelf::create(true),
				nullptr));

		Point point1 = aster->convertToNodeSpace(aster->getPosition());

		//Removes the asteroid once it reaches a certain position
		if (point1.y < visibleSize.height / 2){
			aster->removeChild(aster, true);
		}

} 

void asteroid::changeSpeed() {
	speed = speed / 1.01;
}