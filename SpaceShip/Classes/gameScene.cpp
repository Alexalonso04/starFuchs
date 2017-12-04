#include "gameScene.h" 
#include "GameOverScene.h" //handles the Game Over screen
#include "asteroid.h"  //handles the asteroid class
#include "Ship.h"      //handles the ship class
#include "definitions.h"
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

USING_NS_CC;

//Scene constructor
Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();

	scene->addChild(layer); //adds the layer as a node of the Scene tree
	return scene;
}

//Initializes game components, such as labels, sprites, and physics bodies
bool GameScene::init(){
	//if the layer is not present, return false
	if (!Layer::init()) {
		return false;
	}
	//Variables
	_elapsedTime = 0;

	//Labels_____________________________________________________________________
	//Score label
	score = Label::createWithTTF("Score:", "forgotten futurist rg.ttf", 50);
	score->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	score->setPosition(Director::getInstance()->getVisibleSize().width/2, 247*Director::getInstance()->getVisibleSize().height/256);
	this->addChild(score, 3);

	auto backGround = Sprite::create("background.png");
	backGround->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	backGround->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);
	this->addChild(backGround, 0);
	//___________________________________________________________________________

	//Objects
	spaceship = new Ship(this);

	//Class the update funtion to start running
	this->scheduleUpdate();

	//Event Listener for the keyboard
	auto eventListener = EventListenerKeyboard::create();

	//Possible Delete
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		//If a key already exists, do nothing as it will already have a time stamp
		//Otherwise, set the time stamp to now
		if (keyCodes.find(code) == keyCodes.end()) {
			keyCodes[code] == std::chrono::high_resolution_clock::now();
		}
	};

	//Checks for when a key is released
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event)
	{
		keyCodes.erase(code);
	};

	//Adding the eventListener to event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	//Lets cocos know that there is an update function to be called.
	this->scheduleUpdate();

	this -> schedule(schedule_selector(GameScene::SpawnAsteroid), .25);

	//Event Listener for collisions
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;

}

void GameScene::SpawnAsteroid(float dt) {
	asteroid.SpawnAsteroid(this);
}

//Changes to the Game Over screen and passes "_elapsed time (score)" for display
void GameScene::changeScene() {
	Director::getInstance()->replaceScene(TransitionFade::create(0.75, OverScene::createScene(_elapsedTime))); //scene transition animation
}

//Update function to handle game events and conditions that need to be checked continually
//Handles most of the game logic
void GameScene::update(float secondsCounter) {
	//Node::update(secondsCounter);

	//Adds the elapsed time to the score variable to display at the top
	secondsStream << "SCORE: " << _elapsedTime;
	if (_elapsedTime >= 0) {
		_elapsedTime += static_cast<unsigned>(secondsCounter * 100.0f);
	}
	//adds the current score to the score label
	score->setString(secondsStream.str().c_str());
	secondsStream.str(std::string()); //clears the stream to avoid overlap

	//Ship Movement
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) && isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		spaceship->moveLeft();
		spaceship->moveUp();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) && isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		spaceship->moveLeft();
		spaceship->moveDown();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) && isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		spaceship->moveRight();
		spaceship->moveDown();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) && isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		spaceship->moveRight();
		spaceship->moveUp();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		spaceship->moveLeft();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		spaceship->moveRight();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		spaceship->moveUp();
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		spaceship->moveDown();
	}
}

//Determines if a specified key code is being pressed
bool GameScene::isKeyPressed(EventKeyboard::KeyCode code) {

	//Checks if the code of the key pressed matches the values stored in std::map keyCodes
	if (keyCodes.find(code) != keyCodes.end()) { //Goes through the entire keyCodes map
		return true;
	}
	else {
		return false;
	}
}

//Determines the ammount of time a specified key code is being pressed
//*Posible Delete it
double GameScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	return std::chrono::duration_cast<std::chrono::milliseconds> 
		(std::chrono::high_resolution_clock::now() - keyCodes[code]).count();
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
	//Creates two Physics Body instances that hold their bodies
	PhysicsBody *bodyA = contact.getShapeA()->getBody();
	PhysicsBody *bodyB = contact.getShapeB()->getBody();

	//Boolean to determine whether the collision mask in the definitions matches the collision mask of any the current bodies

	if ((SHIP_COLLISION_BITMASK == bodyA->getCollisionBitmask() && ASTEROID_COLLISION_BITMASK == bodyB->getCollisionBitmask())
		|| (SHIP_COLLISION_BITMASK == bodyB->getCollisionBitmask() && ASTEROID_COLLISION_BITMASK == bodyA->getCollisionBitmask()) ) {
		keyCodes.clear();
		GameScene::changeScene();
		return true;
	}
}

//Because Cocos2dx requires createScene() to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameScene::keyCodes;
