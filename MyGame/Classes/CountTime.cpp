#include "CountTime.h"



void CountTime::Init()
{
	this->setSprite(Sprite::create("CountTime/circle.png"));
	this->getSprite()->setContentSize(size - Size(15, 15));
	countTimer = ProgressTimer::create(this->getSprite());
	countTimer->setType(ProgressTimer::Type::RADIAL);
	countTimer->setPosition(pos);
	countTimer->setPercentage(100);
	countTimer->setReverseProgress(true);
	countTimer->runAction(ProgressTo::create(timeRemain, 0));
	this->layer->addChild(countTimer);
	this->getSprite()->retain();

	CCString* timer = CCString::createWithFormat("%i", timeRemain);
	labelTimer = Label::createWithTTF(timer->getCString(), "fonts/Marker Felt.ttf", 30);
	labelTimer->setPosition(countTimer->getPosition());
	labelTimer->retain();
	this->layer->addChild(labelTimer);
}

void CountTime::Update(float deltaTime)
{
	int percent = (int)countTimer->getPercentage();
	int afterTimeRemain = timeRemain*percent / 100;
	
	if (afterTimeRemain <= 0) {
		labelTimer->setString("");
		timeRemain = 0;
	}
	else {
		CCString* timer = CCString::createWithFormat("%i", afterTimeRemain);
		labelTimer->setString(timer->getCString());
	}
}

void CountTime::startAI(Objject * knight)
{
}

int CountTime::getTimeRemain()
{
	return timeRemain;
}

CountTime::CountTime(Layer* layer, int timeRemain, Vec2 pos, Size size)
{
	this->layer = layer;
	this->timeRemain = timeRemain;
	this->pos = pos;
	this->size = size;
	Init();
}


CountTime::~CountTime()
{
}
