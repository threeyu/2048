#ifndef _CARDSPRITE_H
#define _CARDSPRITE_H

#include "cocos2d.h"


class CardSprite : public cocos2d::Sprite
{
public:
	static CardSprite* createCardSp(int number, int width, int height, cocos2d::Point pos);
	virtual bool init();
	CREATE_FUNC(CardSprite);
	~CardSprite();

	int getNumber();
	void setNumber(int num);
	void runNewNumberAction();
private:
	int number;
	cocos2d::LayerColor* colorBackground;
	cocos2d::Label* labelCardNumber;


	void initCard(int number, int width, int height, cocos2d::Point pos);
};


#endif