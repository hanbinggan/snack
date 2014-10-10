#ifndef __PopLayer_H__
#define __PopLayer_H__

#include "cocos2d.h"
#include "GameScene.h"

class PopLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void ReturnGame(CCObject * pSender);
	void exitGame(CCObject * pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(PopLayer);
};

#endif // __HELLOWORLD_SCENE_H__
