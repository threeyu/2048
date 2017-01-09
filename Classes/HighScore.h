#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include "cocos2d.h"

class HighScore
{
public:
	//static HighScore* myHighScore;

public:
	static HighScore* getInstance();
	static void destroyInstance();

	HighScore();
	~HighScore();

	int getHightScore();
	int getScore();
	void setScore(int score);

private:
	int _score;
	int _highScore;

private:
	bool init();

};

#endif