#include "Poplayer.h"

CCScene* PopLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	PopLayer *layer = PopLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PopLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	int state = CCUserDefault::sharedUserDefault()->getIntegerForKey("state");
	CCMenuItemImage * ReturnGBottom = CCMenuItemImage::create(
		"Restart1.png",
		"Restart2.png",
		this,
		menu_selector(PopLayer::ReturnGame));
	ReturnGBottom->setPosition(ccp(origin.x + visibleSize.width / 4 + ReturnGBottom->getContentSize().width / 2,
		origin.y + ReturnGBottom->getContentSize().height / 2));


	CCMenuItemImage * exitBottom = CCMenuItemImage::create(
		"Exit1.png",
		"Exit2.png",
		this,
		menu_selector(PopLayer::exitGame));
	exitBottom->setPosition(ccp(origin.x + visibleSize.width / 4 * 3 + ReturnGBottom->getContentSize().width / 2,
		origin.y + ReturnGBottom->getContentSize().height / 2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(ReturnGBottom, exitBottom, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label


	// add "HelloWorld" splash screen"
	CCSprite* pSprite;
	if (state == 1)
		pSprite= CCSprite::create("dead.png");
	else if (state == 2)
	{
		pSprite = CCSprite::create("win.png");
	}

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	return true;
}


void PopLayer::ReturnGame(CCObject * pSender)
{
	CCScene * pScene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void PopLayer::exitGame(CCObject * pSender)
{
	CCDirector::sharedDirector()->end();
}

