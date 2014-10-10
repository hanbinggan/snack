#include "GameScene.h"

int rect[] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
int director[][2] = { 0, 1, 0, -1, -1, 0, 1, 0 };

CCScene * GameScene::scene()
{
	CCScene * scene = CCScene::create();
	GameScene * layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint orign = CCDirector::sharedDirector()->getVisibleOrigin();
	memset(mark, 0, sizeof(mark));
	memset(sign, 0, sizeof(sign));
	memset(foodContent, 0, sizeof(foodContent));
	memset(food, 0, sizeof(food));
	memset(a, 0, sizeof(a));
	for (int i = 0; i < 21; i++) //墙初始化
	{
		mark[i][0] = 1;
		mark[0][i] = 1;
		mark[i][20] = 1;
		mark[20][i] = 1;
	}
	mark[1][1] = 8; //蛇的标记
	mark[1][2] = 4;
	mark[1][3] = 2;
	a[0] = 8;
	a[1] = 4;
	a[2] = 2;
	sumTotal = 14;//总的数目
	headTotal = 2;//蛇头的数目
	count = 3;//蛇的长度
	sign[0][0] = 1; //蛇的坐标
	sign[0][1] = 1;
	sign[1][0] = 1;
	sign[1][1] = 2;
	sign[2][0] = 1;
	sign[2][1] = 3;
	dir = 0;//方向初始化为向上 
	life = 3;
	gameSpeed = 300;
	srand(time(0));
	/*do 
	{
		nextFX = rand() % 21;
		nextFY = rand() % 21;
		nextN = rand() % 6;
	} while (mark[nextFX][nextFY]);

	nextFX = 1;
	nextFY = 6;
	nextN = 0;*/
	int foodnum = 0;
	while (foodnum < 4)
	{
		do
		{
			nextFX = rand() % 21;
			nextFY = rand() % 21;
			nextN = rand() % 6;
		} while (mark[nextFX][nextFY]);
		food[foodnum][0] = nextFX;
		food[foodnum][1] = nextFY;
		foodContent[foodnum++] = nextN;
		mark[nextFX][nextFY] = rect[nextN];
	}

//	mark[nextFX][nextFY] = rect[nextN];
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			sprite[i][j] = CCSprite::create(CCString::createWithFormat("%d.png", mark[i][j])->getCString());
			sprite[i][j]->setPosition(ccp(i * 25+12, j * 25+12));
			this->addChild(sprite[i][j], 1);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	/*CCSprite * backGround1 = CCSprite::create("up.png");
	CCSize size  = backGround1->getContentSize();
	CCScale9Sprite * backGround = CCScale9Sprite::create("up.png");
	CCControlButton*button = CCControlButton::create(backGround);
	button->setPosition(ccp(orign.x + visibleSize.width*0.9, orign.y + visibleSize.height* 0.7));
	button->setPreferredSize(CCSizeMake(size.width,size.height));
	this->addChild(button, 2);
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::menuUp1), CCControlEventTouchDown);*/
	//////////////////////////////////////////////////////////////////////////

	CCMenuItemImage * up = CCMenuItemImage::create("Up.png", "Up.png",
		this, menu_selector(GameScene::menuUp));
	up->setPosition(ccp(orign.x + visibleSize.width - up->getContentSize().width*1.5, orign.y + 2.5*up->getContentSize().height));

	CCMenuItemImage * down = CCMenuItemImage::create("Down.png", "Down.png",
		this, menu_selector(GameScene::menuDown));
	down->setPosition(ccp(orign.x + visibleSize.width - down->getContentSize().width*1.5, orign.y + 0.5* down->getContentSize().height));

	CCMenuItemImage * left = CCMenuItemImage::create("Left.png", "Left.png",
		this, menu_selector(GameScene::menuLeft));
	left->setPosition(ccp(orign.x + visibleSize.width - left->getContentSize().width*2.5, orign.y + left->getContentSize().height*1.5));

	CCMenuItemImage * right = CCMenuItemImage::create("Right.png", "Right.png",
		this, menu_selector(GameScene::menuRight));
	right->setPosition(ccp(orign.x + visibleSize.width - right->getContentSize().width*0.5, orign.y + right->getContentSize().height*1.5));

	CCMenuItemImage * pEnd = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		this,
		menu_selector(GameScene::menuEnd));
	pEnd->setPosition(ccp(orign.x + visibleSize.width - pEnd->getContentSize().width / 2,
		orign.y + visibleSize.height - pEnd->getContentSize().height / 2));

	CCMenu * pMenu = CCMenu::create(up, down, left, right, pEnd, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);

	char life_tag[30], totalnum_tag[30];
	sprintf(life_tag, "Life: %d", life);
	sprintf(totalnum_tag, "TotalNum: %d", sumTotal);
	lifeTag = CCLabelTTF::create(life_tag, "Arial", 20);
	totalnumTag = CCLabelTTF::create(totalnum_tag, "Arial", 20);
	lifeTag->setPosition(ccp(orign.x + visibleSize.width - totalnumTag->getContentSize().width, orign.y + visibleSize.height* 0.9));
	totalnumTag->setPosition(ccp(orign.x + visibleSize.width - totalnumTag->getContentSize().width, orign.y + visibleSize.height*0.7));
	this->addChild(lifeTag, 1);
	this->addChild(totalnumTag, 1);

	this->setTouchEnabled(true);
	//this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::step), gameSpeed / 1000.0);

	/*CCSprite *m_rocker_bg = CCSprite::create("Rocker_bg.png");		//摇杆背景
	CCSprite *m_rocker = CCSprite::create("Rocker_bf.png");			//摇杆前面的小球
	this->addChild(m_rocker, 3);
	this->addChild(m_rocker_bg, 3);
	m_rocker_bg->setVisible(false);
	m_rocker->setVisible(false);*/
	return true;
}



/*void GameScene::menuUp1(CCObject * pScender, CCControlEvent controlEvent)
{
	dir = 0;
}*/
void GameScene::menuUp(CCObject * pSender)
{
	dir = 0;
	//test();
}

void GameScene::menuDown(CCObject * pSender)
{
	dir = 1;
	//test();
}

void GameScene::menuLeft(CCObject * pSender)
{
	dir = 2;
	//test();
}

void GameScene::menuRight(CCObject * pSender)
{
	dir = 3;
	//test();
}

void GameScene::menuEnd(CCObject * pSender)
{
	CCDirector::sharedDirector()->end();
}

//void GameScene::update(float dt)
void GameScene::step(float dt)
{
	int x = sign[count-1][0] + director[dir][0];
	int y = sign[count-1][1] + director[dir][1];

	int tempnum = -0xfffff;
	for (int i = 0; i < 4; i++)
	{
		if (x == food[i][0] && y == food[i][1])
		{
			tempnum = i;
			break;
		}
	}

	//if (mark[x][y] == 1 || (mark[x][y]!=0 && !(x == nextFX && y == nextFY)))
	if (mark[x][y] == 1 || (mark[x][y] != 0 &&tempnum < 0))
	{
		if (life > 0)
			life--;
		else
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("state", 1);
			CCUserDefault::sharedUserDefault()->flush();
			CCDirector::sharedDirector()->replaceScene(PopLayer::scene());
		}
		memset(mark, 0, sizeof(mark));
		memset(a, 0, sizeof(a));
		memset(sign, 0, sizeof(sign));
		for (int i = 0; i < 21; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				this->removeChild(sprite[i][j], true);
			}
		}
		for (int i = 0; i < 21; i++) //墙初始化
		{
			mark[i][0] = 1;
			mark[0][i] = 1;
			mark[i][20] = 1;
			mark[20][i] = 1;
		}
		mark[1][1] = 8; //蛇的标记
		mark[1][2] = 4;
		mark[1][3] = 2;
		a[0] = 8;
		a[1] = 4;
		a[2] = 2;
		sumTotal += 14;//总的数目
		headTotal = 2;//蛇头的数目
		count = 3;//蛇的长度
		sign[0][0] = 1; //蛇的坐标
		sign[0][1] = 1;
		sign[1][0] = 1;
		sign[1][1] = 2;
		sign[2][0] = 1;
		sign[2][1] = 3;
		dir = 0;//方向初始化为向上
		for (int i = 0; i < 4; i++)
		{
			mark[food[i][0]][food[i][1]] = rect[foodContent[i]];
		}
//		gameSpeed = 800;
		/*srand(time(0));
		do
		{
			nextFX = rand() % 21;
			nextFY = rand() % 21;
			nextN = rand() % 6;
		} while (mark[nextFX][nextFY]);

		mark[nextFX][nextFY] = rect[nextN];*/
	}
	else if (tempnum >= 0)
	{
		nextN = foodContent[tempnum];
		nextFX = food[tempnum][0];
		nextFY = food[tempnum][1];
		for (int i = 0; i < count; i++)
		{
			mark[sign[i][0]][sign[i][1]] = 0;
		}
		count++;
		a[count - 1] = rect[nextN];
		sumTotal += rect[nextN];
		headTotal = rect[nextN];
		sign[count - 1][0] = x;
		sign[count - 1][1] = y;

		int temp = count-2;

		while (headTotal == a[temp]&&temp >= 0)
		{
			a[temp + 1] = 0;
			headTotal += a[temp];
			a[temp] *= 2;
			if (headTotal == 2048)
			{
				CCUserDefault::sharedUserDefault()->setIntegerForKey("state", 2);
				CCUserDefault::sharedUserDefault()->flush();
				CCDirector::sharedDirector()->replaceScene(PopLayer::scene());
			}
			temp--;
		}
		temp = count - 2 - temp;
		for (int i = 0; i < count - temp; i++)
		{
			sign[i][0] = sign[i + temp][0];
			sign[i][1] = sign[i + temp][1];
		}
		count -= temp;
		for (int i = 0; i < count; i++)
		{
			mark[sign[i][0]][sign[i][1]] = a[i];
		}
		srand(time(0));
		do
		{
			nextFX = rand() % 21;
			nextFY = rand() % 21;
			nextN = rand() % 6;
		} while (mark[nextFX][nextFY]);
		foodContent[tempnum] = nextN;
		food[tempnum][0] = nextFX;
		food[tempnum][1] = nextFY;
		mark[nextFX][nextFY] = rect[nextN];
	}
	else
	{
		mark[sign[0][0]][sign[0][1]] = 0;
		for (int i = 0; i < count-1; i++)
		{
			sign[i][0] = sign[i+1][0];
			sign[i][1] = sign[i+1][1];
		}
		sign[count-1][0] = x;
		sign[count-1][1] = y;
		for (int i = 0; i < count; i++)
		{
			mark[sign[i][0]][sign[i][1]] = a[i];
		}
	}
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			this->removeChild(sprite[i][j]);
		}
	}

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			sprite[i][j] = CCSprite::create(CCString::createWithFormat("%d.png", mark[i][j])->getCString());
			sprite[i][j]->setPosition(ccp(i * 25+12, j * 25+12));
			this->addChild(sprite[i][j], 2);
		}
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint orign = CCDirector::sharedDirector()->getVisibleOrigin();
	this->removeChild(lifeTag);
	this->removeChild(totalnumTag);
	char life_tag[30], totalnum_tag[30];
	sprintf(life_tag, "Life: %d", life);
	sprintf(totalnum_tag, "TotalNum: %d", sumTotal);
	lifeTag = CCLabelTTF::create(life_tag, "Arial", 20);
	totalnumTag = CCLabelTTF::create(totalnum_tag, "Arial", 20);
	lifeTag->setPosition(ccp(orign.x + visibleSize.width - totalnumTag->getContentSize().width, orign.y + visibleSize.height* 0.9));
	totalnumTag->setPosition(ccp(orign.x + visibleSize.width - totalnumTag->getContentSize().width, orign.y + visibleSize.height*0.7));
	this->addChild(lifeTag, 1);
	this->addChild(totalnumTag, 1);
}

/*CCPoint startTouchLocation;
bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//获得起始touch 的坐标
	CCLOG("$$$$$ %p",m_rocker_bg);
	startTouchLocation = pTouch->getLocationInView();
	startTouchLocation = CCDirector::sharedDirector()->convertToGL(startTouchLocation);
	//m_rocker_bg->setPosition(ccp(50,50));
	m_rocker_bg->setPosition(startTouchLocation);
	m_rocker_bg->setVisible(true);
	m_rocker->setPosition(startTouchLocation);
	m_rocker->setVisible(true);
	return true;
}
void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//获得当前touch坐标
	CCPoint pos = pTouch->getLocationInView();
	pos = CCDirector::sharedDirector()->convertToGL(pos);
	float dx = pos.x - startTouchLocation.x;
	float dy = pos.y - startTouchLocation.y;
	float posDis = sqrt(dx*dx + dy*dy);
	if (posDis > 100)
	{
		m_rocker->setPosition(CCPoint(startTouchLocation.x + dx * 100 / posDis, startTouchLocation.y + dy * 100 / posDis));
	}
	else
	{
		m_rocker->setPosition(pos);
	}
	if (fabs(dx) < 10)dx = 0;
	if (fabs(dy) < 10)dy = 0;
	double dd = 1;
	if (!(dx == 0 && dy == 0))
		dd = sqrt(dx*dx + dy*dy);
}
void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	m_rocker_bg->setVisible(false);
	m_rocker->setVisible(false);
}
void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	m_rocker_bg->setVisible(false);
	m_rocker->setVisible(false);
}
void GameScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}*/