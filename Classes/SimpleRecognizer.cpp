#include "SimpleRecognizer.h"

USING_NS_CC;

SimpleRecognizer::SimpleRecognizer()
{
	this->result = SimpleGesturesError;
}

void SimpleRecognizer::beginPoint(cocos2d::Point point)
{
	this->result = SimpleGesturesError;
	pointsVec.clear();
	pointsVec.push_back(point);
}

void SimpleRecognizer::movePoint(cocos2d::Point point)
{
	pointsVec.push_back(point);
}

SimpleGestures SimpleRecognizer::endPoint(cocos2d::Point point)
{
	pointsVec.push_back(point);

	if(this->pointsVec.size() < 3)
		return SimpleGesturesError;

	SimpleGestures newResult = SimpleGesturesError;
	int len = this->pointsVec.size();
	double dx = this->pointsVec[len - 1].x - this->pointsVec[0].x;
	double dy = this->pointsVec[len - 1].y - this->pointsVec[0].y;

	
	if(abs(dx) > abs(dy))//在这种情况下,运动趋势的触点在x轴方向
		newResult = dx > 0? SimpleGesturesRight : SimpleGesturesLeft;
	else//在这种情况下,运动趋势的触点在y轴方向
		newResult = dy > 0? SimpleGesturesUp : SimpleGesturesDown;

	if(result == SimpleGesturesError)
		result = newResult;

	if(result != newResult)
		result = SimpleGesturesNotSupport;

	return result;
}

std::vector<cocos2d::Point>& SimpleRecognizer::getPoints()
{
	return this->pointsVec;
}

SimpleRecognizer::~SimpleRecognizer()
{

}

