#pragma once

#include "cocos2d.h"
#include <chrono>
#include "Ship.h"
#include "asteroid.h"
class GameScene : public cocos2d::Layer{
public:
	//Methods
	static cocos2d::Scene* createScene(); //Creates a new scene
	virtual bool init(); //Initializes all the game components
	void changeScene(); //Changes to the GameOver Screen
	virtual void update(float secondsCounter) override; //the update funtion for the scene
	
	//Methods for ship movement
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);


	//Member Variables
	//defined these here to be used in multiple functions in cpp
	unsigned int _elapsedTime; //holds the elapse time since the game started
	std::stringstream secondsStream; //a string stream to hold the time passed

	CREATE_FUNC(GameScene);
private:
	//Member Variables
	cocos2d::Label* score; //label for the score of the game
	static std::map<cocos2d::EventKeyboard::KeyCode, 
		   std::chrono::high_resolution_clock::time_point> keyCodes; /*variable of type map that holds the key that was pressed and the
																 ammount of time that key was pressed */
	cocos2d::Label *label; 
	Ship *spaceship; //pointer to the ship object

	void SpawnAsteroid(float dt); //spawn asteroid function
	asteroid asteroid;  //asteroid variable

	//Member Functions
	bool onContactBegin(cocos2d::PhysicsContact &contact); //Function to handle collisions
};