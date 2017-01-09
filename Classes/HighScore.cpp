#include "HighScore.h"

#define HIGHSCORETAG "HighScore"

USING_NS_CC;

static HighScore* myHighScore = NULL;

HighScore::HighScore()
{
	//myHighScore = NULL;
	_highScore = 0;
	_score = 0;
}

HighScore::~HighScore()
{

}

HighScore* HighScore::getInstance()
{
	if(!myHighScore)
	{
		myHighScore = new HighScore();
		myHighScore->init();
	}
	return myHighScore;
}

bool HighScore::init()
{
	_highScore = UserDefault::getInstance()->getIntegerForKey(HIGHSCORETAG);
	return true;
}

int HighScore::getHightScore()
{
	return this->_highScore;
}

int HighScore::getScore()
{
	return this->_score;
}

void HighScore::setScore(int score)
{
	this->_score = score;
	if(score > this->_highScore)
	{
		this->_highScore = score;
		UserDefault::getInstance()->setIntegerForKey(HIGHSCORETAG, score);
	}
}

void HighScore::destroyInstance()
{
	if(myHighScore)
	{
		CC_SAFE_DELETE(myHighScore);
	}
}




