#ifndef _GAMEOVERLAYER_H
#define _GAMEOVERLAYER_H

#include "cocos2d.h"

class GameOverLayer : public cocos2d::LayerColor
{
public:
	static GameOverLayer* create(const cocos2d::Color4B& color);
	virtual bool initWithColor(const cocos2d::Color4B& color);


	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* e);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* e);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e);

private:
	void onReStart(Ref* pSender);

};


#endif