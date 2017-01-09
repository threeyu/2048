#include "CardSprite.h"

USING_NS_CC;

CardSprite* CardSprite::createCardSp(int number, int width, int height, cocos2d::Point pos)
{
	CardSprite* card = new CardSprite();
	if(card && card->init())
	{
		card->autorelease();
		card->initCard(number, width, height, pos);
		
		return card;
	}
	CC_SAFE_DELETE(card);

	return NULL;
}

CardSprite::~CardSprite()
{

}

bool CardSprite::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void CardSprite::runNewNumberAction()
{
	auto action = ScaleBy::create(0.05, 0.99);
	runAction(Sequence::create(action, action->reverse(), nullptr));
}


int CardSprite::getNumber()
{
	return number;
}

void CardSprite::setNumber(int num)
{
	this->number = num;

	//������ʾ������
	if (num > 0)
	{
		labelCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
	}
	else
	{
		labelCardNumber->setString("");
	}

	//�������ִ�С
	if (num >= 0)
	{
		labelCardNumber->setSystemFontSize(100);
	}
	if (num >= 16)
	{
		labelCardNumber->setSystemFontSize(90);
	}
	if (num >= 128)
	{
		labelCardNumber->setSystemFontSize(60);
	}
	if (num >= 1024)
	{
		labelCardNumber->setSystemFontSize(40);
	}

	//�ж����ֵĴ�С��������ɫ
	if(number == 0){
		colorBackground->setColor(Color3B(200,190,180));
	}
	if (number == 2) {
		colorBackground->setColor(Color3B(240,230,220));
	}
	if (number == 4) {
		colorBackground->setColor(Color3B(240,220,200));
	}
	if (number == 8) {
		colorBackground->setColor(Color3B(240,180,120));
	}
	if (number == 16) {
		colorBackground->setColor(Color3B(240,140,90));
	}
	if (number == 32) {
		colorBackground->setColor(Color3B(240,120,90));
	}
	if (number == 64) {
		colorBackground->setColor(Color3B(240,90,60));
	}
	if (number == 128) {
		colorBackground->setColor(Color3B(240,90,60));
	}
	if (number == 256) {
		colorBackground->setColor(Color3B(240,200,70));
	}
	if (number == 512) {
		colorBackground->setColor(Color3B(240,200,70));
	}
	if (number == 1024) {
		colorBackground->setColor(Color3B(0,130,0));
	}
	if (number == 2048) {
		colorBackground->setColor(Color3B(0,130,0));
	}
}

void CardSprite::initCard(int number, int wight, int height, Point position)
{
	//��ʼ������
	this->number = number;
	//���뿨Ƭ������ɫ
	colorBackground = LayerColor::create(Color4B(200,190,180,255), wight-15, height-15);
	colorBackground->setPosition(position);

	//�ж��������0����ʾ������Ͳ���ʾ
	if (number > 0)
	{
		//��������
		labelCardNumber = Label::createWithSystemFont(__String::createWithFormat("%i", number)->getCString(), "Consolas", 100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2, colorBackground->getContentSize().height/2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}
	else
	{
		//��������
		labelCardNumber = Label::createWithSystemFont("", "Consolas", 100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2, colorBackground->getContentSize().height/2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}

	this->addChild(colorBackground);
}








