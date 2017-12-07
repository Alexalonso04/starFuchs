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

	//Labels__________________________________________________________________________________________________________________________
	//Game Over Label
	auto over = Label::createWithTTF("GAME\nOVER", "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/Gabato.ttf", 160);
	over->setColor(ccc3(255, 0, 0));
	over->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	over->setPosition(Director::getInstance()->getVisibleSize().width/2, 25*Director::getInstance()->getVisibleSize().height/32);

	//Final Score Label
	auto score = Label::createWithTTF("Final Score and High Scores:", "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 60);
	score->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	score->setPosition(Director::getInstance()->getVisibleSize().width/2, 75* Director::getInstance()->getVisibleSize().height/128);

	//makes int into string to be used in 'last' label
	String * tempScore = String::createWithFormat("%i", gameScore);

	//Last highScore
	auto last = Label::createWithTTF(tempScore->getCString(), "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 50);
	last->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	last->setPosition(Director::getInstance()->getVisibleSize().width/2, 35* Director::getInstance()->getVisibleSize().height/64);

	//Try Again Label
	auto again = Label::createWithTTF("Try again?", "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 90);
	again->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	again->setPosition(Director::getInstance()->getVisibleSize().width/2, 21* Director::getInstance()->getVisibleSize().height/64);

	//User input label
	auto answer = Label::createWithTTF("Y / N", "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 70);
	answer->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	answer->setPosition(Director::getInstance()->getVisibleSize().width/2, 15* Director::getInstance()->getVisibleSize().height/64);
	//________________________________________________________________________________________________________________________________

	//Sprite__________________________________________________________________________________________________________________________
	auto backGround = Sprite::create("C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/gameOverbackground.png");
	backGround->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	backGround->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);
	//________________________________________________________________________________________________________________________________

	//Adds each label and sprite to the scene tree
	this->addChild(over, 1);
	this->addChild(score, 1);
	this->addChild(again, 1);
	this->addChild(answer, 1);
	this->addChild(last, 1);
	this->addChild(backGround, 0);

	//Part of the cocos2dx databse
	UserDefault * def = UserDefault::getInstance();
	
	//Assigns three variables to the get first 3 high scores
	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
	auto second = def->getIntegerForKey("SECOND", 0);
	auto third = def->getIntegerForKey("THIRD", 0);

	//Determines the top 3 high-scores
	if (gameScore > highScore) {
		third = second;
		second = highScore;
		highScore = gameScore;

		def->setIntegerForKey("HIGHSCORE", highScore);
	}
	else if (gameScore > second && gameScore < highScore) {
		third = second;
		second = gameScore;

		def->setIntegerForKey("SECOND", second);
	}

	else if (gameScore > third && gameScore < second && gameScore < highScore) {
		third = gameScore;

		def->setIntegerForKey("THIRD", third);
	}


	def->flush(); //deletes the databse to avoid being overdrawn

	//Displaying top 3 high schores
	//High Score 1

	String * tempFirst = String::createWithFormat("%i", highScore); //string to hold the formatted score

	//Label to display the formatted score
	auto highest = Label::createWithTTF(tempFirst->getCString(), "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 50);
	highest->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	highest->setPosition(Director::getInstance()->getVisibleSize().width/2, 31* Director::getInstance()->getVisibleSize().height / 64);
	highest->setColor(ccc3(215, 215, 0));

	this->addChild(highest, 1); //Adds the label to the scene tree

	//High Score 2
	String * tempSecond = String::createWithFormat("%i", second); //string to hold the formatted score

	//Label to display the score
	auto higher = Label::createWithTTF(tempSecond->getCString(), "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 50);
	higher->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	higher->setPosition(Director::getInstance()->getVisibleSize().width / 2, 57* Director::getInstance()->getVisibleSize().height / 128);
	higher->setColor(ccc3(100, 215, 0));

	this->addChild(higher, 1); //adds the label to the scene tree

	//High Score 3
	String * tempThird = String::createWithFormat("%i", third);

	auto high = Label::createWithTTF(tempThird->getCString(), "C:/Users/Alejandro Alonso/Documents/starFuchs/SpaceShip/proj.win32/forgotten futurist rg.ttf", 50);
	high->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	high->setPosition(Director::getInstance()->getVisibleSize().width / 2, 13* Director::getInstance()->getVisibleSize().height / 32);
	high->setColor(ccc3(255, 0, 0));

	this->addChild(high, 1);

	//Creates an event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(OverScene::changeScene, this); //runs a function on callback
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //feeds the event listener to a dispatcher to run

	return true;
}

//Changes the scenes to the previous scene or to the welcome scene
void OverScene::changeScene(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Y) {
		Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, GameScene::createScene())); //scene transition 
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_N) {
		Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5, WelcomeScene::createScene())); 
	}
}