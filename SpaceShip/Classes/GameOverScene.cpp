#include "GameOverScene.h"
#include "welcomeScene.h"
#include "gameScene.h"

USING_NS_CC;

unsigned int gameScore;

Scene* OverScene::createScene(unsigned int tempScore)
{
	//gets passed score from gameScene for use as final score
	gameScore = tempScore;

	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = OverScene::create();

	scene->addChild(layer);

	return scene;
}

bool OverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto over = Label::createWithTTF("GAME\nOVER", "Gabato.ttf", 160);
	over->setColor(ccc3(255, 0, 0));
	over->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	over->setPosition(Director::getInstance()->getVisibleSize().width/2, 25*Director::getInstance()->getVisibleSize().height/32);

	auto score = Label::createWithTTF("Final Score and High Scores:", "forgotten futurist rg.ttf", 60);
	score->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	score->setPosition(Director::getInstance()->getVisibleSize().width/2, 75* Director::getInstance()->getVisibleSize().height/128);

	//makes int into string to be used in 'last' label
	String * tempScore = String::createWithFormat("%i", gameScore);

	auto last = Label::createWithTTF(tempScore->getCString(), "forgotten futurist rg.ttf", 50);
	last->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	last->setPosition(Director::getInstance()->getVisibleSize().width/2, 35* Director::getInstance()->getVisibleSize().height/64);

	auto again = Label::createWithTTF("Try again?", "forgotten futurist rg.ttf", 90);
	again->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	again->setPosition(Director::getInstance()->getVisibleSize().width/2, 21* Director::getInstance()->getVisibleSize().height/64);

	auto answer = Label::createWithTTF("Y / N", "forgotten futurist rg.ttf", 70);
	answer->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	answer->setPosition(Director::getInstance()->getVisibleSize().width/2, 15* Director::getInstance()->getVisibleSize().height/64);

	auto backGround = Sprite::create("gameOverbackground.png");
	backGround->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	backGround->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);

	this->addChild(over, 1);
	this->addChild(score, 1);
	this->addChild(again, 1);
	this->addChild(answer, 1);
	this->addChild(last, 1);
	this->addChild(backGround, 0);

	UserDefault * def = UserDefault::getInstance();

	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
	auto second = def->getIntegerForKey("SECOND", 0);
	auto third = def->getIntegerForKey("THIRD", 0);

	if (gameScore > highScore) {
		third = second;
		second = highScore;
		highScore = gameScore;

		def->setIntegerForKey("HIGHSCORE", highScore);
	}


	if (gameScore > second && gameScore < highScore) {
		third = second;
		second = gameScore;

		def->setIntegerForKey("SECOND", second);
	}

	if (gameScore > third && gameScore < second && gameScore < highScore) {
		third = gameScore;

		def->setIntegerForKey("THIRD", third);
	}

	def->flush();

	String * tempFirst = String::createWithFormat("%i", highScore);

	auto highest = Label::createWithTTF(tempFirst->getCString(), "forgotten futurist rg.ttf", 50);
	highest->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	highest->setPosition(Director::getInstance()->getVisibleSize().width/2, 31* Director::getInstance()->getVisibleSize().height / 64);
	highest->setColor(ccc3(215, 215, 0));

	this->addChild(highest, 1);

	String * tempSecond = String::createWithFormat("%i", second);

	auto higher = Label::createWithTTF(tempSecond->getCString(), "forgotten futurist rg.ttf", 50);
	higher->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	higher->setPosition(Director::getInstance()->getVisibleSize().width / 2, 57* Director::getInstance()->getVisibleSize().height / 128);
	higher->setColor(ccc3(100, 215, 0));

	this->addChild(higher, 1);

	String * tempThird = String::createWithFormat("%i", third);

	auto high = Label::createWithTTF(tempThird->getCString(), "forgotten futurist rg.ttf", 50);
	high->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	high->setPosition(Director::getInstance()->getVisibleSize().width / 2, 13* Director::getInstance()->getVisibleSize().height / 32);
	high->setColor(ccc3(255, 0, 0));

	this->addChild(high, 1);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(OverScene::changeScene, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void OverScene::changeScene(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Y) {
		Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, GameScene::createScene()));
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_N) {
		Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5, WelcomeScene::createScene()));
	}
}