#ifndef __Game_Scene_H__
#define __Game_Scene_H__

#include <cstring>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "PopLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace extension;

class GameScene :public CCLayer
{
public:
	static CCScene * scene();
	CREATE_FUNC(GameScene);
private:
	int dir;
	int life;
	int count;
	int nextN;
	int nextFX;
	int nextFY;
	int sumTotal;
	int gameSpeed;
	int headTotal;
	CCLabelTTF * lifeTag;
	CCLabelTTF * totalnumTag;
	int a[100];
	int food[4][2];
	int foodContent[4];
	int mark[21][21];
	int sign[100][2];
	CCSprite * sprite[21][21];

	virtual bool init();
	void step(float dt);
	//void update(float dt);
	void menuUp(CCObject * pSender);
	void menuDown(CCObject * pSender);
	void menuLeft(CCObject * pSender);
	void menuRight(CCObject * pSender);
	void menuEnd(CCObject * pScender);

	/*CCSprite *m_rocker_bg;
	CCSprite *m_rocker;
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent);*/
//	void test();

	//void menuUp1(CCObject * pScender,CCControlEvent controlEvent);
};

#endif