#include "Knight.h"



void Knight::Init()
{
	this->setSprite(Sprite::create("Main_charactor/fight_1.png"));
	layer->addChild(this->getSprite());
	this->getSprite()->setAnchorPoint(Vec2(0.5, 0));
	this->getSprite()->setPosition(100, 100);
	this->setBlood(BLOOD);

	auto physic = PhysicsBody::createBox(this->getSprite()->getContentSize());
	physic->setDynamic(false);
	physic->setRotationEnable(false);
	physic->setGravityEnable(false);
	physic->setContactTestBitmask(1);
	physic->setCollisionBitmask(KNIGHT_TAG);
	this->getSprite()->setPhysicsBody(physic);
	this->getSprite()->retain();
	this->getSprite()->setTag(KNIGHT_TAG);
	

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

	// skill
	Vector<SpriteFrame*> animateSkills;
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

	// Fire
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fire/Fire.plist", "Fire/Fire.png");
	Vector<SpriteFrame*> animateFire;
	animateFire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire_1.png"));
	animateFire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire_2.png"));
	animateFire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire_3.png"));
	animateFire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire_4.png"));
	animateFire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire_5.png"));
	animateFire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire_6.png"));
	animateFire.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fire_7.png"));

	// animation fire
	animation = Animation::createWithSpriteFrames(animateFire, 0.2f);
	aniFire = Animate::create(animation);

	// retain
	aniFight->retain();
	aniGo->retain();
	aniRun->retain();
	aniWait->retain();
	aniFire->retain();


	// create fire
	fire = Sprite::create("Fire/fire_alone.png");
	this->layer->addChild(fire);
	fire->setPosition(Vec2(-100, -100));

	auto physics = PhysicsBody::createBox(fire->getContentSize());
	physics->setDynamic(true);
	physics->setRotationEnable(false);
	physics->setGravityEnable(false);
	physics->setContactTestBitmask(1);
	physics->setCollisionBitmask(FIRE_TAG);
	fire->setPhysicsBody(physics);
	fire->setTag(FIRE_TAG);

	// create blood bar
	createBloodBar();
}

void Knight::Update(float deltaTime)
{
	bloodbg->setPosition(this->getSprite()->getPosition() + Vec2(0, this->getSprite()->getContentSize().height));
	blood->setPosition(bloodbg->getPosition());
	blood->setPercent(this->getBlood());
}

Knight::Knight(Layer* layer)
{
	this->layer = layer;
	Init();
}

void Knight::startAI(Objject* knight)
{
	setState(state::START);
}

void Knight::fight()
{
	if (currentState != state::GO && currentState != state::RUN) {
		setState(state::FIGHT);
	}
}

void Knight::skill()
{
	if (currentState != state::GO && currentState != state::RUN && currentState != state::FIGHT) {
		setState(state::K_SKILL);
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
	case state::K_SKILL: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(aniFight);


			if (fire->getNumberOfRunningActions() == 0) {
				fire->setPosition(this->getSprite()->getPosition() + Vec2(0, this->getSprite()->getContentSize().width / 2));
				if(!isLeft) moveBy = MoveBy::create(0.3, Vec2(250, 0));
				else moveBy = MoveBy::create(0.3, Vec2(-250, 0));
				auto moveTo = MoveTo::create(0.01, Vec2(-500, -500));
				auto sequence = Sequence::create(moveBy, aniFire, moveTo, nullptr);
				fire->runAction(sequence);
			
			}
		}

		break;
	}
	default:
		break;
	}

	currentState = nextState;
}

void Knight::createBloodBar()
{
	bloodbg = ui::LoadingBar::create("Bar/hud_bg.png");
	this->layer->addChild(bloodbg, 100);

	this->blood = ui::LoadingBar::create("Bar/hud_blood.png");
	blood->setPercent(this->getBlood());
	blood->setDirection(ui::LoadingBar::Direction::LEFT);
	this->layer->addChild(blood, 200);

	// set scale
	bloodbg->setScale(SCALE_BLOOD_BAR);
	blood->setScale(SCALE_BLOOD_BAR);
}

void Knight::IsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

Knight::~Knight()
{
}
