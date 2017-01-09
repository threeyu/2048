#include "GameScene.h"
#include "CardSprite.h"
#include "SimpleRecognizer.h"
#include "HighScore.h"
#include "GameOverLayer.h"
USING_NS_CC;


Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	GameScene* layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

GameScene::~GameScene()
{
	delete _recognizer;

}

bool GameScene::init()
{
	if(!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();


	// 背景
	auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);
	
	// 分数
	_score = 0;
	auto cardNumTitle = Label::createWithSystemFont("SCORE", "Consolas", 80);
	cardNumTitle->setPosition(Point(visibleSize.width - 150, visibleSize.height / 2 + 250));
	this->addChild(cardNumTitle);

	_cardNumTTF = Label::createWithSystemFont("0", "Consolas", 70);
	_cardNumTTF->setPosition(Point(visibleSize.width - 150, visibleSize.height / 2 + 180));
	this->addChild(_cardNumTTF);

	// 暂停
	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	auto menuItemPause = MenuItemFont::create("PAUSE", CC_CALLBACK_1(GameScene::onPause, this));

	auto pauseMenu = Menu::create(menuItemPause, NULL);
	pauseMenu->setPosition(Point(visibleSize.width - 150, visibleSize.height / 2));
	this->addChild(pauseMenu);

	// 退出
	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	auto menuItemExit = MenuItemFont::create("EXIT", CC_CALLBACK_1(GameScene::onExit, this));

	auto exitMenu = Menu::create(menuItemExit, NULL);
	exitMenu->setPosition(Point(visibleSize.width - 150, visibleSize.height / 3));
	this->addChild(exitMenu);

	// 设置触摸事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// 创建卡片
	_cellSize = 0;
	_cellSpace = 10;
	createCardSp(visibleSize);
	if (UserDefault::getInstance()->getBoolForKey("history"))
	{
		resumeStatus();
	}
	else
	{
		//初始时生成两个2
		createCardNum(false);
		createCardNum(false);
	}

	// 手势
	_recognizer = new SimpleRecognizer();


	return true;
}

void GameScene::createCardSp(Size size)
{
	_cellSize = (size.width / 2 - _cellSpace * 3 - 40) / 4;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//需要屏幕分辨率适配
			CardSprite *card = CardSprite::createCardSp(0, _cellSize, _cellSize, getPosition(i, j));
			_cardArr[i][j] = card;
			this->addChild(card);
		}
	}
}
Point GameScene::getPosition(int i, int j)
{
	float pX = 20 + _cellSpace / 2 + i * (_cellSize + _cellSpace);
	float pY = _cellSize / 2 + j * (_cellSize + _cellSpace);

	return Point(pX, pY);
}

void GameScene::createCardNum(bool animation)
{
	while (1) 
	{
		int i = CCRANDOM_0_1() * 4;        //生成0~3随机数
		int j = CCRANDOM_0_1() * 4;

		log("[%d][%d]",i,j);

		if (_cardArr[i][j]->getNumber() == 0)
		{
			//2和4的生成率为9:1
			_cardArr[i][j]->setNumber(CCRANDOM_0_1()*10 < 1 ? 4 : 2);
			if(animation)
			{
				_cardArr[i][j]->runNewNumberAction();
			}
			break;
		}

		if (!shouldCreateCardNumber()) {
			break;
		}
	}
}
bool GameScene::shouldCreateCardNumber()
{
	bool isCreate = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if( 0 == _cardArr[i][j]->getNumber() )
			{
				isCreate = true;
				break;
			}
		}
	}

	return isCreate;
}

void GameScene::onPause(Ref* pSender)
{
	log("+++++++++++++ pause ++++++++++++++");
}

void GameScene::onExit(Ref* pSender)
{
	exit(0);
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* e)
{
	Point point = touch->getLocation();
	_recognizer->beginPoint(point);

	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* e)
{
	Point point = touch->getLocation();
	_recognizer->movePoint(point);
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e)
{
	Point point = touch->getLocation();
	SimpleGestures gesture = _recognizer->endPoint(point);

	switch (gesture)
	{
	case SimpleGesturesUp:
		log("up");
		doUp();
		doCheck();
		setScore(_score);
		break;
	case SimpleGesturesDown:
		log("down");
		doDown();
		doCheck();
		setScore(_score);
		break;
	case SimpleGesturesLeft:
		log("left");
		doLeft();
		doCheck();
		setScore(_score);
		break;
	case SimpleGesturesRight:
		log("right");
		doRight();
		doCheck();
		setScore(_score);
		break;
	case SimpleGesturesError:
		log("error");
		break;
	case SimpleGesturesNotSupport:
		break;
	default:
		break;
	}

}

bool GameScene::doUp()
{
	bool isMove = false;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 3; j >= 0; j--)
		{
			for(int j1 = j - 1; j1 >= 0; j1--)
			{
				if(_cardArr[i][j1]->getNumber() > 0)
				{
					if(_cardArr[i][j]->getNumber() <= 0)
					{
						_cardArr[i][j]->setNumber(_cardArr[i][j1]->getNumber());
						_cardArr[i][j1]->setNumber(0);
						
						j++;
						isMove = true;
					}
					else if(_cardArr[i][j]->getNumber() == _cardArr[i][j1]->getNumber())
					{
						_cardArr[i][j]->setNumber(_cardArr[i][j1]->getNumber() * 2);
						_cardArr[i][j1]->setNumber(0);

						_score += _cardArr[i][j]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}


bool GameScene::doDown()
{
	bool isMove = false;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			for(int j1 = j + 1; j1 < 4; ++j1)
			{
				if(_cardArr[i][j1]->getNumber() > 0)
				{
					if(_cardArr[i][j]->getNumber() <= 0)
					{
						_cardArr[i][j]->setNumber(_cardArr[i][j1]->getNumber());
						_cardArr[i][j1]->setNumber(0);

						j--;
						isMove = true;
					}
					else if(_cardArr[i][j]->getNumber() == _cardArr[i][j1]->getNumber())
					{
						_cardArr[i][j]->setNumber(_cardArr[i][j1]->getNumber() * 2);
						_cardArr[i][j1]->setNumber(0);

						_score += _cardArr[i][j]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}


bool GameScene::doLeft()
{
	bool isMove = false;
	for(int j = 0; j < 4; ++j)
	{
		for(int i = 0; i < 4; ++i)
		{
			for(int i1 = i + 1; i1 < 4; ++i1)
			{
				if(_cardArr[i1][j]->getNumber() > 0)
				{
					if(_cardArr[i][j]->getNumber() <= 0)
					{
						_cardArr[i][j]->setNumber(_cardArr[i1][j]->getNumber());
						_cardArr[i1][j]->setNumber(0);

						i--;
						isMove = true;
					}
					else if(_cardArr[i][j]->getNumber() == _cardArr[i1][j]->getNumber())
					{
						_cardArr[i][j]->setNumber(_cardArr[i1][j]->getNumber() * 2);
						_cardArr[i1][j]->setNumber(0);

						_score += _cardArr[i][j]->getNumber();
						isMove = true;
					}

					break;
				}
			}
		}
	}

	return isMove;
}

bool GameScene::doRight()
{
	bool isMove = false;
	for(int j = 0; j < 4; ++j)
	{
		for(int i = 3; i >= 0; i--)
		{
			for(int i1 = i - 1; i1 >= 0; i1--)
			{
				if(_cardArr[i1][j]->getNumber() > 0)
				{
					if(_cardArr[i][j]->getNumber() <= 0)
					{
						_cardArr[i][j]->setNumber(_cardArr[i1][j]->getNumber());
						_cardArr[i1][j]->setNumber(0);

						i++;
						isMove = true;
					}
					else if(_cardArr[i][j]->getNumber() == _cardArr[i1][j]->getNumber())
					{
						_cardArr[i][j]->setNumber(_cardArr[i1][j]->getNumber() * 2);
						_cardArr[i1][j]->setNumber(0);

						_score += _cardArr[i][j]->getNumber();
						isMove = true;
					}

					break;
				}
			}
		}
	}

	return isMove;
}

void GameScene::doCheck()
{
	bool isGameOver = true;

	// 结束边界  4*4的card数值>0 且  相邻card没有相同数值
	// 4*4的card数值>0 不能在创建Number
	// 判断每一个的上下左右和自己是否相同
	for(int j = 0; j < 4; ++j)
	{
		for(int i = 0; i < 4; ++i)
		{
			if(_cardArr[i][j]->getNumber() == 0 ||
				(i > 0 && _cardArr[i][j]->getNumber() == _cardArr[i - 1][j]->getNumber()) ||
				(i < 3 && _cardArr[i][j]->getNumber() == _cardArr[i + 1][j]->getNumber()) ||
				(j > 0 && _cardArr[i][j]->getNumber() == _cardArr[i][j - 1]->getNumber()) ||
				(j < 3 && _cardArr[i][j]->getNumber() == _cardArr[i][j + 1]->getNumber()))
			{
				isGameOver = false;
			}
		}
		//log("%d %d %d %d", _cardArr[j][0]->getNumber(), _cardArr[j][1]->getNumber(), _cardArr[j][2]->getNumber(), _cardArr[j][3]->getNumber());
	}

	if(isWin())
	{


		return;
	}

	if(isGameOver)
	{
		log("+++game over+++");
		UserDefault::getInstance()->setBoolForKey("history", false);

		HighScore::getInstance()->setScore(_score);
		GameOverLayer* gameOverLayer = GameOverLayer::create(Color4B(0, 0, 0, 180));
		this->addChild(gameOverLayer);

		Director::getInstance()->pause();
	}
	else
	{
		log("+++continue++");
		if(shouldCreateCardNumber())
		{
			createCardNum(false);
			saveStatus();
		}

	}
}

bool GameScene::isWin()
{
	bool result = false;
	for(int x = 0; x < 4; ++x)
	{
		for(int y = 0; y < 4; ++y)
		{
			if(_cardArr[x][y]->getNumber() == 2048)
			{
				result = true;
				break;
			}
		}
	}

	return result;
}


void GameScene::resumeStatus()
{
	char tempArr[10];
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			sprintf(tempArr, "%d%d", i, j);
			int num = UserDefault::getInstance()->getIntegerForKey(tempArr);
			_cardArr[i][j]->setNumber(num);
		}
		//log("%d %d %d %d", _cardArr[i][0]->getNumber(), _cardArr[i][1]->getNumber(), _cardArr[i][2]->getNumber(), _cardArr[i][3]->getNumber());
	}

	_score = UserDefault::getInstance()->getIntegerForKey("score");
	setScore(_score);

	UserDefault::getInstance()->setBoolForKey("history", false);
}


void GameScene::saveStatus()
{
	char tempArr[10];
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			sprintf(tempArr, "%d%d", i, j);
			UserDefault::getInstance()->setIntegerForKey(tempArr, _cardArr[i][j]->getNumber());
		}
	}

	UserDefault::getInstance()->setIntegerForKey("score", _score);
	UserDefault::getInstance()->setBoolForKey("history", true);
}

void GameScene::setScore(int score)
{
	_cardNumTTF->setString(__String::createWithFormat("%i", score)->getCString());
}



