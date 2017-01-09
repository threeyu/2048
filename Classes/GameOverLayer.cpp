#include "GameOverLayer.h"
#include "HighScore.h"
#include "GameScene.h"

USING_NS_CC;

GameOverLayer* GameOverLayer::create(const cocos2d::Color4B& color)
{
	GameOverLayer* layer = new GameOverLayer();
	if(layer && layer->initWithColor(color))
	{
		layer->autorelease();
		return layer;
	}

	CC_SAFE_DELETE(layer);
	return NULL;
}

bool GameOverLayer::initWithColor(const cocos2d::Color4B& color)
{
	if(!LayerColor::initWithColor(color))
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Point centerPos = Point(winSize.width / 2, winSize.height / 2);

	// 标题
	auto title = Label::createWithSystemFont("GAME OVER", "Consolas", 80);
	title->setPosition(centerPos.x, centerPos.y + 150);
	this->addChild(title);

	// 得分
	char scoreArr[64];
	sprintf(scoreArr, "%d", HighScore::getInstance()->getScore());
	auto scoreTitle = Label::createWithSystemFont(scoreArr, "Consolas", 80);
	scoreTitle->setPosition(centerPos.x, centerPos.y - 50);
	this->addChild(scoreTitle);

	// 重开
	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	auto menuItemReStart = MenuItemFont::create("RESTART", CC_CALLBACK_1(GameOverLayer::onReStart, this));

	auto reStartMenu = Menu::create(menuItemReStart, NULL);
	reStartMenu->setPosition(centerPos.x, centerPos.y - 150);
	this->addChild(reStartMenu);

	// 触摸事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameOverLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameOverLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	touchListener->setSwallowTouches(true);


	return true;
}

void GameOverLayer::onReStart(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
	Director::getInstance()->resume();
}

bool GameOverLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* e)
{

	return true;
}

void GameOverLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* e)
{

}

void GameOverLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e)
{

}
