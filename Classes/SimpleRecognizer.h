#ifndef _SimpleRecognizer_H
#define _SimpleRecognizer_H

#include "cocos2d.h"

typedef enum
{
	SimpleGesturesUp,
	SimpleGesturesDown,
	SimpleGesturesLeft,
	SimpleGesturesRight,
	SimpleGesturesError,
	SimpleGesturesNotSupport
}SimpleGestures;

class SimpleRecognizer
{
public:
	SimpleRecognizer();
	~SimpleRecognizer();

	void beginPoint(cocos2d::Point point);
	void movePoint(cocos2d::Point point);
	SimpleGestures endPoint(cocos2d::Point point);

	std::vector<cocos2d::Point>& getPoints();

protected:
	double x;
	double y;
	SimpleGestures result;
	std::vector<cocos2d::Point> pointsVec;

};



#endif