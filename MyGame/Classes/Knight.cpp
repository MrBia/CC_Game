#include "Knight.h"



void Knight::Init()
{
	this->setSprite(Sprite::create("Main_charactor/fight_1.png"));
	layer->addChild(this->getSprite());
	this->getSprite()->setAnchorPoint(Vec2(0.5, 0));
	this->getSprite()->setPosition(100, 100);

	auto physic = PhysicsBody::createBox(this->getSprite()->getContentSize());
	physic->setDynamic(true);
	physic->setRotationEnable(false);
	physic->setGravityEnable(false);
	this->getSprite()->setPhysicsBody(physic);
	this->getSprite()->retain();

	// state
	currentState = state::START;

	// read plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Main_charactor/knight.plist", "Main_charactor/knight.png");

	// fight
	Vector<SpriteFrame*> animateFights;
	animateFights.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_1.png"));
	animateFights.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_2.png"));
	animateFights.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_3.png"));
	animateFights.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_4.png"));
	animateFights.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_5.png"));
	animateFights.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fight_6.png"));

	// go
	Vector<SpriteFrame*> animateGoes;
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go1.png"));
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go2.png"));
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go3.png"));
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go4.png"));
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go5.png"));
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go6.png"));
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go7.png"));
	animateGoes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("go8.png"));

	// run
	Vector<SpriteFrame*> animateRuns;
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run1.png"));
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run2.png"));
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run3.png"));
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run4.png"));
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run5.png"));
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run6.png"));
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run7.png"));
	animateRuns.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("run8.png"));

	// wait
	Vector<SpriteFrame*> animateWaits;
	animateWaits.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("wait1.png"));
	animateWaits.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("wait2.png"));
	animateWaits.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("wait3.png"));

	// animations
	auto animation = Animation::createWithSpriteFrames(animateFights, 0.2f);
	aniFight = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(animateGoes, 0.2f);
	aniGo = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(animateRuns, 0.2f);
	aniRun = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(animateWaits, 0.2f);
	aniWait = Animate::create(animation);


	// retain
	aniFight->retain();
	aniGo->retain();
	aniRun->retain();
	aniWait->retain();
}

void Knight::Update(float deltaTime)
{
}

Knight::Knight(Layer* layer)
{
	this->layer = layer;
	Init();
}

void Knight::start()
{
	setState(state::START);
}

void Knight::fight()
{
	if (currentState != state::GO && currentState != state::RUN) {
		setState(state::FIGHT);
	}
}

void Knight::go()
{
	setState(state::GO);
}

void Knight::run()
{
	setState(state::RUN);
}

void Knight::setState(int nextState)
{
	switch (nextState)
	{
	case state::START: {
		/*if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(aniWait);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(aniWait);
		}*/

		if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(aniWait);
		}

		break;
	}
	case state::RUN: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(aniRun);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(aniRun);
		}

		break;
	}
	case state::GO: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(aniGo);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(aniGo);
		}
		break;
	}
	case state::FIGHT: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(aniFight);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(aniFight);
		}
		
		break;
	}
	default:
		break;
	}

	currentState = nextState;
}


Knight::~Knight()
{
}
