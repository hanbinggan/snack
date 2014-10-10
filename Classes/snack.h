///HelloWorldScene.h:
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"


#include "SimpleAudioEngine.h"


class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();


//a selector starting
	void menuOnNewGame(CCObject* pSender);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);


    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};


#endif  // __HELLOWORLD_SCENE_H__
/////HelloWorldScene.cpp
#include "HelloWorldScene.h"
#include "GreedyChopper.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);


        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);


        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);


    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////


        CC_BREAK_IF(! CCLayer::init());


        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////


        // 1. Add a menu item with "X" image, which is clicked to quit the program.


        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);


        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));


		CCMenuItemImage *pStartItem = CCMenuItemImage::create(
			"newGame.jpg",
			"newGame1.jpg",
			this,
			menu_selector(HelloWorld::menuOnNewGame));
		CC_BREAK_IF(!pStartItem);
		pStartItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2 - 20, 30));


        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, pStartItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);


        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);


        // 2. Add a label shows "Hello World".


        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Greedy Chopper", "MarkerFelt-Thin", 24);
        CC_BREAK_IF(! pLabel);


        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, 70));


        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);


        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("welcome.jpg");
        CC_BREAK_IF(! pSprite);


        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));


        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);


        bRet = true;
    } while (0);


    return bRet;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


void HelloWorld::menuOnNewGame(CCObject* pSender)
{
//到游戏页面
	CCScene* scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);


		GreedyChopper* p = GreedyChopper::create();
		CC_BREAK_IF(!p);


		scene->addChild(p);
		CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::transitionWithDuration(0.5f, scene));


	} while (0);
}
//游戏页面：
///GreedyChopper.h:
#ifndef GREEDYCHOPPER_H
#define GREEDYCHOPPER_H


#include "HelloWorldScene.h"
#include "cocos2d.h"


#include "SimpleAudioEngine.h"


class GreedyChopper: public cocos2d::CCLayer
{
public:

	virtual bool init();  
	static cocos2d::CCScene* scene();
	void menuOnNewGame(CCObject* pSender);
    void menuCloseCallback(CCObject* pSender);

	void clickUp(CCObject* pSender);
	void clickDown(CCObject* pSender);
	void clickRight(CCObject* pSender);
	void clickLeft(CCObject* pSender);
	void step(float dt);

	CREATE_FUNC(GreedyChopper);
	private:
	int graph[54][54], chopper[2][100];
	int length, head, tail, direction, beanX, beanY, x, y, level, life, speed;
	int sumTime;
	cocos2d::CCSprite* sprite[54][54];
	bool flag, lifeFlag;
	float gameSpeed;
	cocos2d::CCLabelTTF* levelTag;
	cocos2d::CCLabelTTF* timeTag;
	cocos2d::CCLabelTTF* lifeTag;
	cocos2d::CCLabelTTF* speedTag;
};
#endif

//GreedyChopper.cpp
#include "HelloWorldScene.h"
#include "GreedyChopper.h"

using namespace cocos2d;


CCScene* GreedyChopper::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
		GreedyChopper *layer = GreedyChopper::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}


bool GreedyChopper::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

	memset(graph, 0, sizeof(graph));
	//墙壁
	for (int i = 0; i < 54; i++)
	{
		graph[0][i] = graph[53][i] = 1;
	}
	for (int i = 1; i < 53; i++)
	{
		graph[i][0] = graph[i][53] = 1;
	}
	for (int i = 1; i <= 3; i++)
		graph[1][i] = 2;      //蛇身
		graph[1][4] = 3;          //蛇头
	for (int i = 0; i < 4; i++)
	{
		chopper[0][i] = 1;
		chopper[1][i] = i + 1;
	}                         //记录贪吃蛇所在的坐标
	head = 3, tail = 0, length = 4;
	srand(time(0));
	do
	{
		beanX = rand() % 52 + 1;
		beanY = rand() % 52 + 1;
	} while (graph[beanX][beanY]);  
	graph[beanX][beanY] = 2;         //随机产生食物
	for (int i = 0; i < 54; i++)
	{
		for (int j = 0; j < 54; j++)
		{
			if (graph[i][j] == 1)
				sprite[i][j] = CCSprite::create("wall.jpg");
			else if (graph[i][j] == 2)
				sprite[i][j] = CCSprite::create("tail.jpg");
			else if (graph[i][j] == 3)
				sprite[i][j] = CCSprite::create("head.jpg");
			else
				sprite[i][j] = CCSprite::create("grid.jpg");
			sprite[i][j]->setPosition(ccp(10 * i + 5, 10 * j + 5));
			this->addChild(sprite[i][j], 1);
		}
	}
	//方向默认向上，自动前进速度默认为800ms，等级为1
	life = 3, direction = 1, gameSpeed = 500, level = 1, speed = 10 / (gameSpeed / 1000);
	flag = true, lifeFlag = true;
	sumTime = 0;
	char life_str[30], level_str[30], time_str[30], speed_str[30];
	sprintf(life_str, "Life: %d", life);
	lifeTag = CCLabelTTF::create(life_str, "font09.fnt", 20);
	CC_BREAK_IF(!lifeTag);
	lifeTag->setPosition(ccp(630, 520));
	this->addChild(lifeTag, 1);
	sprintf(level_str, "Level: %d", level);
	levelTag = CCLabelTTF::create(level_str, "font09.fnt", 20);
	CC_BREAK_IF(!levelTag);
	levelTag->setPosition(ccp(630, 490));
	this->addChild(levelTag, 1);
	sprintf(time_str, "Time: %d s", sumTime / 1000);
	timeTag = CCLabelTTF::create(time_str, "font09.fnt", 20);
	CC_BREAK_IF(!levelTag);
	timeTag->setPosition(ccp(630, 460));
	this->addChild(timeTag, 1);
	sprintf(speed_str, "Speed: %d", speed);
	speedTag = CCLabelTTF::create(speed_str, "font09.fnt", 20);
	CC_BREAK_IF(!speedTag);
	speedTag->setPosition(ccp(630, 430));
	this->addChild(speedTag, 1);
	this->schedule(schedule_selector(GreedyChopper::step), gameSpeed / 1000);
	CCMenuItemImage *up = CCMenuItemImage::create(
		"up.jpg",
		"up1.jpg",
		this,
		menu_selector(GreedyChopper::clickUp));
	CC_BREAK_IF(! up);
	up->setPosition(ccp(630, 370));
	CCMenuItemImage *down = CCMenuItemImage::create(
		"down.jpg",
		"down1.jpg",
		this,
		menu_selector(GreedyChopper::clickDown));
	CC_BREAK_IF(! down);
	down->setPosition(ccp(630, 260));
	CCMenuItemImage *right = CCMenuItemImage::create(
		"right.jpg",
		"right1.jpg",
		this,
		menu_selector(GreedyChopper::clickRight));
	CC_BREAK_IF(! right);
	right->setPosition(ccp(685, 315));
	CCMenuItemImage *left = CCMenuItemImage::create(
		"left.jpg",
		"left1.jpg",
		this,
		menu_selector(GreedyChopper::clickLeft));
	CC_BREAK_IF(! left);
	left->setPosition(ccp(575, 315));
       
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GreedyChopper::menuCloseCallback));
      CC_BREAK_IF(! pCloseItem);


        // Place the menu item bottom-right conner.
      pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));


	  CCMenuItemImage *pStartItem = CCMenuItemImage::create(
		  "newGame.jpg",
		  "newGame1.jpg",
		  this,
		  menu_selector(GreedyChopper::menuOnNewGame));
	  CC_BREAK_IF(!pStartItem);
	  pStartItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 150, 20));

	  CCMenu* pMenu = CCMenu::create(up, down, right, left, pCloseItem, pStartItem, NULL);
	  pMenu->setPosition(CCPointZero);
	  CC_BREAK_IF(!pMenu);

	  this->addChild(pMenu, 1);
	  CCSprite* pSprite = CCSprite::create("welcome.jpg");
	  pSprite->setOpacity(90);
	  CC_BREAK_IF(!pSprite);


		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		this->addChild(pSprite, 0);
        bRet = true;
    } while (0);


    return bRet;
}


void GreedyChopper::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


void GreedyChopper::menuOnNewGame(CCObject* pSender)
{
	CCScene* scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		HelloWorld* pScene = HelloWorld::create();
		CC_BREAK_IF(!pScene);
		scene->addChild(pScene);
		CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::transitionWithDuration(0.5, scene));
	} while (0);
}


void GreedyChopper::clickUp(CCObject* pSender)
{
	if (flag)
		direction = 1;
}


void GreedyChopper::clickDown(CCObject* pSender)
{
	if (flag)
		direction = 2;
}


void GreedyChopper::clickRight(CCObject* pSender)
{
	if (flag)
		direction = 3;
}


void GreedyChopper::clickLeft(CCObject* pSender)
{
	if (flag)
	direction = 4;
}


void GreedyChopper::step(float dt)
{
	if (flag)
	sumTime += gameSpeed;
	this->removeChild(timeTag, true);
	char time_str[30];
	sprintf(time_str, "Time: %d s", sumTime / 1000);
	timeTag = CCLabelTTF::create(time_str, "font09.fnt", 20);
	timeTag->setPosition(ccp(630, 460));
	this->addChild(timeTag, 1);
	switch (direction)
	{
		//向上
	case 1: x = chopper[0][head], y = chopper[1][head] + 1, lifeFlag = true;
		break;
	//向下
	case 2: x = chopper[0][head], y = chopper[1][head] - 1, lifeFlag = true;
		break;
		//向右
	case 3: x = chopper[0][head] + 1, y = chopper[1][head], lifeFlag = true;
		break;
	//向左
	case 4: x = chopper[0][head] - 1, y = chopper[1][head], lifeFlag = true;
		break;
	default: x = chopper[0][head], y = chopper[1][head], lifeFlag = false;
		break;
	}
	//贪吃蛇触碰到墙壁，Game Over
	if ((x == 0 || x == 53 || y == 0 || y == 53) || (graph[x][y] && !(x == beanX && y == beanY)))
	{
		if (life && lifeFlag)
			life--;
		this->removeChild(lifeTag, true);
		char life_str[30];
		sprintf(life_str, "Life: %d", life);
		lifeTag = CCLabelTTF::create(life_str, "font09.fnt", 20);
		lifeTag->setPosition(ccp(630, 520));
		this->addChild(lifeTag, 1);
		direction = 0;
		if (!life)
		{
			flag = false;
			CCLabelTTF* pLabel = CCLabelTTF::create("Game Over!", "font09.fnt", 24);
			// Get window size and place the label upper. 
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			pLabel->setPosition(ccp(630, 70));


			// Add the label to HelloWorld layer as a child layer.
			this->addChild(pLabel, 1);
		}
		return;
	}
	else if (x == beanX && y == beanY)
	{
		length++;
		if (length >= 8)
		{
			length -= 8;
			level++;
			if (gameSpeed > 50)
				gameSpeed -= 50;
			this->removeChild(levelTag, true);
			char level_str[30];
			sprintf(level_str, "Level: %d", level);
			levelTag = CCLabelTTF::create(level_str, "font09.fnt", 20);
			levelTag->setPosition(ccp(630, 490));
			this->addChild(levelTag, 1);
			this->removeChild(speedTag, true);
			char speed_str[30];
			speed = 10 / (gameSpeed / 1000);
			sprintf(speed_str, "Speed: %d", speed);
			speedTag = CCLabelTTF::create(speed_str, "font09.fnt", 20);
			speedTag->setPosition(ccp(630, 430));
			this->addChild(speedTag, 1);
		}
		graph[beanX][beanY] = 0;
		graph[chopper[0][head]][chopper[1][head]] = 2;
		head = (head + 1) % 100;
		graph[x][y] = 3;
		chopper[0][head] = x;
		chopper[1][head] = y;
		srand(time(0));
		do
		{
			beanX = rand() % 52 + 1;
			beanY = rand() % 52 + 1;
		} while (graph[beanX][beanY]);
		graph[beanX][beanY] = 2;
	}
	else
	{
		graph[chopper[0][tail]][chopper[1][tail]] = 0;
		tail = (tail + 1) % 100;
		graph[chopper[0][head]][chopper[1][head]] = 2;
		head = (head + 1) % 100;
		graph[x][y] = 3;
		chopper[0][head] = x;
		chopper[1][head] = y;
	}
	for (int i = 0; i < 54; i++)
	{
		for (int j = 0; j < 54; j++)
			this->removeChild(sprite[i][j], true);
	}
	for (int i = 0; i < 54; i++)
	{
		for (int j = 0; j < 54; j++)
		{
			if (graph[i][j] == 1)
				sprite[i][j] = CCSprite::create("wall.jpg");
			else if (graph[i][j] == 2)
				sprite[i][j] = CCSprite::create("tail.jpg");
			else if (graph[i][j] == 3)
				sprite[i][j] = CCSprite::create("head.jpg");
			else
				sprite[i][j] = CCSprite::create("grid.jpg");
			sprite[i][j]->setPosition(ccp(10 * i + 5, 10 * j + 5));
				this->addChild(sprite[i][j], 1);
		}
	}
}