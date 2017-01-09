#ifndef _GAMESCENE_H
#define  _GAMESCENE_H

#include "cocos2d.h"

class CardSprite;
class SimpleRecognizer;


class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	~GameScene();
	cocos2d::Point getPosition(int i, int j);

	
private:
	int _cellSize;
	int _cellSpace;
	int _score;// 分数
	CardSprite* _cardArr[4][4];// 存卡片
	cocos2d::Label* _cardNumTTF;// 显示分数控件
	SimpleRecognizer* _recognizer;// 手势

private:
	void createCardSp(cocos2d::Size size);
	void createCardNum(bool animation = true);
	bool shouldCreateCardNumber();

	void onPause(Ref* pSender);
	void onExit(Ref* pSender);

	// 触摸事件
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* e);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* e);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e);

	// 上下左右
	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();

	bool isWin();
	void resumeStatus();
	void saveStatus();
	void doCheck();// 判断
	void setScore(int score);
};

#endif