#include "Zombie.h"



void Zombie::Init()
{
	this->setSprite(Sprite::create("Zombie/zombie_1_1.png"));
	layer->addChild(this->getSprite());
	this->getSprite()->setAnchorPoint(Vec2(1, 0));
	this->setBlood(BLOOD);


	auto physic = PhysicsBody::createBox(this->getSprite()->getContentSize());
	physic->setDynamic(false);
	physic->setRotationEnable(false);
	physic->setGravityEnable(false);
	physic->setGroup(this->index);
	physic->setContactTestBitmask(1);
	physic->setCollisionBitmask(ZOMBIE_TAG);
	this->getSprite()->setPhysicsBody(physic);
	this->getSprite()->retain();
	this->getSprite()->setTag(ZOMBIE_TAG);

	// state
	currentState = stateZombie::Z_START;

	// read plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Zombie/zombie.plist", "Zombie/zombie.png");

	// fight1
	Vector<SpriteFrame*> ani_Fight_1;
	ani_Fight_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_1.png"));
	ani_Fight_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_2.png"));
	ani_Fight_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_3.png"));
	ani_Fight_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_4.png"));
	ani_Fight_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_5.png"));
	ani_Fight_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_6.png"));
	ani_Fight_1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_7.png"));

	// fight2
	Vector<SpriteFrame*> ani_Fight_2;
	ani_Fight_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_2_1.png"));
	ani_Fight_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_2_2.png"));
	ani_Fight_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_2_3.png"));
	ani_Fight_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_2_4.png"));
	ani_Fight_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_2_5.png"));
	ani_Fight_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_2_6.png"));
	ani_Fight_2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_2_7.png"));

	// die
	Vector<SpriteFrame*> ani_Die;
	ani_Die.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_3_1.png"));
	ani_Die.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_3_2.png"));
	ani_Die.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_3_3.png"));
	ani_Die.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_3_4.png"));
	ani_Die.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_3_5.png"));

	// start
	Vector<SpriteFrame*> ani_Start;
	ani_Start.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_1.png"));
	ani_Start.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("zombie_1_2.png"));

	// animation
	auto animation = Animation::createWithSpriteFrames(ani_Fight_1, 0.2f);
	animationFight_1 = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(ani_Fight_2, 0.2f);
	animationFight_2 = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(ani_Die, 0.2f);
	animationDie = Animate::create(animation);
	animation = Animation::createWithSpriteFrames(ani_Start, 0.2f);
	animationStart = Animate::create(animation);

	// retain
	animationFight_1->retain();
	animationFight_2->retain();
	animationDie->retain();
	animationStart->retain();


	// create blood bar
	createBloodBar();
}

void Zombie::Update(float deltaTime)
{
	bloodbg->setPosition(this->getSprite()->getPosition() + Vec2(0, this->getSprite()->getContentSize().height));
	blood->setPosition(bloodbg->getPosition());
	blood->setPercent(this->getBlood());
}

void Zombie::startAI(Objject* knight)
{
	setState(currentState);
	float dis = distance(this, knight);

	if (this->getBlood() > 0) {
		life = true;
	}
	else {
		life = false;
	}

	if (life) {
		if (dis < DISTANCE_FIGHT_Z) {
			if (this->getBlood() > 90) {
				normalFight();
			}
			else {
				skillFight();
			}
		}
		else {
			setState(stateZombie::Z_START);
		}
	}
	else {
		die();
	}
}

void Zombie::normalFight()
{
	setState(stateZombie::NORMAL_FIGHT);
}

void Zombie::skillFight()
{
	setState(stateZombie::SKILL_FIGHT);
}

void Zombie::die()
{
	setState(stateZombie::DIE);
}

void Zombie::setState(int nextState)
{
	switch (nextState)
	{
	case stateZombie::Z_START: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animationStart);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animationStart);
		}
		break;
	}
	case stateZombie::NORMAL_FIGHT: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animationFight_1);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0){
			this->getSprite()->runAction(animationFight_1);
		}
		break;
	}
	case stateZombie::SKILL_FIGHT: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animationFight_2);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->runAction(animationFight_2);
		}
		break;
	}
	case stateZombie::DIE: {
		if (nextState != currentState) {
			this->getSprite()->stopAllActions();
			this->getSprite()->runAction(animationDie);
		}
		else if (this->getSprite()->getNumberOfRunningActions() == 0) {
			this->getSprite()->setVisible(false);
			this->getSprite()->getPhysicsBody()->setEnabled(false);
		}
		break;
	}
	default:
		break;
	}

	currentState = nextState;
}

void Zombie::createBloodBar()
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

float Zombie::distance(Objject * zombie, Objject * knight)
{
	Vec2 posZB = zombie->getSprite()->getPosition();
	Vec2 posKN = knight->getSprite()->getPosition();

	float dis = sqrt((posZB.x - posKN.x)*(posZB.x - posKN.x) + (posZB.y - posKN.y)*(posZB.y - posKN.y));

	return dis;
}

Zombie::Zombie(Layer* layer, int index)
{
	this->layer = layer;
	this->index = index;
	Init();
}

Zombie::~Zombie()
{
}
