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

	//welcome and start labels
	auto label = Label::createWithTTF("The New\n Frontier", "software_tester_7.ttf", 130);
	label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	label->setPosition(400, 1090);
	label->setColor(ccc3(235, 200, 0));

	auto start = Label::createWithTTF("Press enter\nto begin!", "forgotten futurist rg.ttf", 70);
	start->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	start->setPosition(400, 575);
	start->setColor(ccc3(255, 255, 255));

	auto backGround = Sprite::create("welcomeBackground.png");
	backGround->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	backGround->setPosition(400, 640);

	this->addChild(label, 1);
	this->addChild(start, 1);
	this->addChild(backGround, 0);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(WelcomeScene::changeScene, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void WelcomeScene::changeScene(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER) {
		Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, GameScene::createScene()));
	}
}

