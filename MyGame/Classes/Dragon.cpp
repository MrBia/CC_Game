#include "Dragon.h"



Dragon::Dragon(Layer* layer)
{
	this->layer = layer;
	Init();
}


void Dragon::Init()
{
	this->setSprite(Sprite::create("Dragon/fireUp_1.png"));
	layer->addChild(this->getSprite());
	//this->getSprite()->setAnchorPoint(Vec2(0.5, 0));
	this->getSprite()->setPosition(Vec2(400, 100));

	auto physic = PhysicsBody::createBox(this->getSprite()->getContentSize());
	physic->setDynamic(true);
	physic->setRotationEnable(false);
	physic->setGravityEnable(false);
	this->getSprite()->setPhysicsBody(physic);
	this->getSprite()->retain();

	// state
	currentState = stateDragon::D_START;

	// read plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Dragon/dragon.plist", "Dragon/dragon.png");

	// start
	Vector<SpriteFrame*> aniStart;
	aniStart.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_9.png"));
	aniStart.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_10.png"));
	aniStart.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_11.png"));

	// fire up
	Vector<SpriteFrame*> aniFire_Up;
	aniFire_Up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireUp_1.png"));
	aniFire_Up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireUp_2.png"));
	aniFire_Up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireUp_3.png"));
	aniFire_Up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireUp_4.png"));
	aniFire_Up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireUp_5.png"));
	aniFire_Up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireUp_6.png"));
	aniFire_Up.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireUp_7.png"));

	// fire down normal
	Vector<SpriteFrame*> aniFireNormal;
	aniFireNormal.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_1_1.png"));
	aniFireNormal.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_1_2.png"));
	aniFireNormal.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_1_3.png"));
	aniFireNormal.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_1_4.png"));
	aniFireNormal.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_1_5.png"));
	aniFireNormal.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_1_6.png"));

	// fire down skill
	Vector<SpriteFrame*> aniFireSkill;
	aniFireSkill.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_2_1.png"));
	aniFireSkill.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_2_2.png"));
	aniFireSkill.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_2_3.png"));
	aniFireSkill.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_2_4.png"));
	aniFireSkill.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fireDown_2_5.png"));

	// jump
	Vector<SpriteFrame*> aniJump;
	aniJump.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_1.png"));
	aniJump.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_2.png"));
	aniJump.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_3.png"));

	// fly
	Vector<SpriteFrame*> aniFly;
	aniFly.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_4.png"));
	aniFly.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_5.png"));
	aniFly.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_6.png"));

	// stop
	Vector<SpriteFrame*> aniStop;
	aniStop.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_7.png"));
	aniStop.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_8.png"));
	aniStop.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_9.png"));
	aniStop.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_10.png"));
	aniStop.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_11.png"));

	// die
	Vector<SpriteFrame*> aniDie;
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_1.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_2.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_3.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_4.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_5.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_6.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_7.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_8.png"));
	aniDie.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("die_9.png"));

	// create animation
	auto animation = Animation::createWithSpriteFrames(aniStart, 0.2f);
	animateStart = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(aniFire_Up, 0.2f);
	animateFireUp = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(aniFireNormal, 0.2f);
	animateFireDownNormal = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(aniFireSkill, 0.2f);
	animateFireDownSkill = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(aniJump, 0.2f);
	animateJump = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(aniFly, 0.2f);
	animateFly = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(aniStop, 0.2f);
	animateStop = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(aniDie, 0.2f);
	animateDie = Animate::create(animation);

	// retain
	animateStart->retain();
	animateFireUp->retain();
	animateFireDownNormal->retain();
	animateFireDownSkill->retain();
	animateJump->retain();
	animateFly->retain();
	animateStop->retain();
	animateDie->retain();
}

void Dragon::Update(float deltaTime)
{
}

void Dragon::setState(int nextState)
{
	switch (nextState)
	{
	case stateDragon::D_START: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animateStart);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animateStart);
		}
		break;
	}
	case stateDragon::FIRE_UP: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animateFireUp);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animateFireUp);
		}
		break;
	}
	case stateDragon::FIRE_DOWN_NORMAL: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animateFireDownNormal);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animateFireDownNormal);
		}
		break;
	}
	case stateDragon::FIRE_DOWN_SKILL: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animateFireDownSkill);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animateFireDownSkill);
		}
		break;
	}
	case stateDragon::FLY: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			auto sequence = Sequence::create(animateJump, animateFly, nullptr);
			this->getSprite()->runAction(sequence);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animateFly);
		}
		break;
	}
	case stateDragon::STOP: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animateStop);
		}
		break;
	}
	case stateDragon::D_DIE: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animateDie);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animateDie);
		}
		break;
	}
	default:
		break;
	}

	currentState = nextState;
}

void Dragon::start()
{
	setState(stateDragon::D_START);
}

void Dragon::fireUp()
{
	setState(stateDragon::FIRE_UP);
}

void Dragon::fireDownNormal()
{
	setState(stateDragon::FIRE_DOWN_NORMAL);
}

void Dragon::fireDownSkill()
{
	setState(stateDragon::FIRE_DOWN_SKILL);
}

void Dragon::fly()
{
	setState(stateDragon::FLY);
}

void Dragon::stop()
{
	setState(stateDragon::STOP);
}

void Dragon::die()
{
	setState(stateDragon::D_DIE);
}

Dragon::~Dragon()
{
}
