#include "AppDelegate.h"
#include "gameScene.h"
#include "GameOverScene.h"
#include "welcomeScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Hello World");
		glview->setFrameSize(800, 1280);
		glview->setDesignResolutionSize(800, 1280, ResolutionPolicy::EXACT_FIT);
		director->setOpenGLView(glview);
	}

	auto scene = WelcomeScene::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}
