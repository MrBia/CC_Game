#include "Soul.h"



void Soul::startAI(Objject * knight)
{
}

void Soul::Init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Effect.plist", "Effect.png");

	Vector<SpriteFrame*> spriteFrame;
	spriteFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("flyy_1.png"));
	spriteFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("flyy_2.png"));
	spriteFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("flyy_3.png"));
	spriteFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("flyy_5.png"));
	spriteFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("flyy_6.png"));
	spriteFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("flyy_7.png"));
	spriteFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("flyy_8.png"));

	auto animation = Animation::createWithSpriteFrames(spriteFrame, 0.1f);
	auto animate = Animate::create(animation);
	animate->retain();

	auto sprite = Sprite::create();
	sprite->setScale(0.1);
	sprite->setPosition(Vec2(-100, -100));
	layer->addChild(sprite);
	sprite->runAction(RepeatForever::create(animate));
	this->setSprite(sprite);
}

void Soul::Update(float deltaTime)
{
}

Soul::Soul(Layer* layer)
{
	this->layer = layer;
	Init();
}


Soul::~Soul()
{
}
