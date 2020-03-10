#include "..\Classes\CountTime.h"



void CountTime::Init()
{
	this->setSprite(Sprite::create("CountTime/circle.png"));
	auto countTimer = ProgressTimer::create(this->getSprite());
	countTimer->setType(ProgressTimer::Type::RADIAL);
	countTimer->setPercentage(100);
	countTimer->setReverseProgress(true);
	countTimer->runAction(ProgressTo::create(timeRemain, 0));
	this->layer->addChild(countTimer);
	this->getSprite()->retain();
	this->getSprite()->setPosition(100, 100);

	CCString* timer = CCString::createWithFormat("%i", timeRemain);
	labelTimer = Label::createWithTTF(timer->getCString(), "fonts/Marker Felt.ttf", 30);
	labelTimer->setPosition(countTimer->getPosition());
	labelTimer->retain();
	this->layer->addChild(labelTimer);
}

void CountTime::Update(float deltaTime)
{
	static float i = 0;
	i += deltaTime;
	if (i >= 1) {
		timeRemain--;
		i = 0;
	}

	CCString* timer = CCString::createWithFormat("%i", timeRemain);
	labelTimer->setString(timer->getCString());
}

void CountTime::startAI(Objject * knight)
{
}

CountTime::CountTime(Layer* layer, int timeRemain)
{
	this->layer = layer;
	this->timeRemain = timeRemain;
	Init();
}


CountTime::~CountTime()
{
}
