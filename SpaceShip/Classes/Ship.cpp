#include "Ship.h"
#include "definitions.h"
USING_NS_CC;

Ship::Ship(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleSize();

	//Create ship sprite and set position
	ship = cocos2d::Sprite::create("fighter-01.png");
	ship->setPosition(visibleSize.width/2, 5* Director::getInstance()->getVisibleSize().height/64);
	ship->setScale(0.10);
	
	//Creating the physics body for the ship, creating the collision bitmasks, and setting the sprite to the physics body
	auto shipBody = cocos2d::PhysicsBody::createCircle(ship->getContentSize().width / 2);
	shipBody->setCollisionBitmask(SHIP_COLLISION_BITMASK);
	shipBody->setContactTestBitmask(true);
	shipBody->setGravityEnable(false);
	ship->setPhysicsBody(shipBody);

	layer->addChild(ship, 100);
}

void Ship::moveLeft()
{
	if ( (ship->getPositionX() >= 100) )
	{
		ship->setPosition(ship->getPositionX() - 6, ship->getPositionY());
	}
}

void Ship::moveRight()
{
	if ((ship->getPositionX() <= visibleSize.width-100))
	{
		ship->setPosition(ship->getPositionX() + 6, ship->getPositionY());
	}
}

void Ship::moveUp()
{
	if ((ship->getPositionY() <= visibleSize.height - 150))
	{
		ship->setPosition(ship->getPositionX(), ship->getPositionY() + 6);
	}
}

void Ship::moveDown()
{
	if ((ship->getPositionY() >= 100))
	{
		ship->setPosition(ship->getPositionX(), ship->getPositionY() - 6);
	}
}




