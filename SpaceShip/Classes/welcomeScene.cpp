#include "welcomeScene.h"
#include "gameScene.h"


USING_NS_CC;

Scene* WelcomeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();

	scene->addChild(layer);

	return scene;
}

bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//Labels_________________________________________________________________________________________________________________________________________________________________________
	//Game name label
	auto label = Label::createWithTTF("STAR\n FUCHS", "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/software_tester_7.ttf", 160);
	label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	label->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height - Director::getInstance()->getVisibleSize().height/6);
	label->setColor(ccc3(235, 200, 0));
	
	//Instruction label
	auto start = Label::createWithTTF("Press enter\nto begin!", "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 70);
	start->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	start->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);
	start->setColor(ccc3(255, 255, 255));

	auto move = Label::createWithTTF("Use the arrow \nkeys to move!", "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 70);
	move->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	move->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 3);
	move->setColor(ccc3(255, 255, 255));
	this->addChild(move, 1);


	//_______________________________________________________________________________________________________________________________________________________________________________

	//Background Sprite
	auto backGround = Sprite::create("C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/welcomeBackground.png");
	backGround->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	backGround->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);

	//Adds all the sprites and labels to the scene tree
	this->addChild(label, 1);
	this->addChild(start, 1);
	this->addChild(backGround, 0);


	//Creates an event listener for keyboard input
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(WelcomeScene::changeScene, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//Changes the scene to the game screen
void WelcomeScene::changeScene(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER) {
		Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, GameScene::createScene()));
	}
}

