#include "AppDelegate.h"
#include "gameScene.h"
#include "GameOverScene.h"
#include "welcomeScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate(){
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance(); //creates an instance of the director, which handles every execution
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Hello World");
		//1000, 16000
		glview->setFrameSize(900, 1440); //sets the frame size of the game
		glview->setDesignResolutionSize(800, 1280, ResolutionPolicy::EXACT_FIT); //sets the resolution to fit the frame size of the game
		director->setOpenGLView(glview);
	}
	
	//Creates a instance of the welcome scene, which is the first scene that runss
	auto scene = WelcomeScene::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}
