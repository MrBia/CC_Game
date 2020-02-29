#include "GamePlay.h"



Scene * GamePlay::createGame()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GamePlay::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlay::init()
{
	if (!Layer::init()) {
		return false;
	}

	// create edge
	//createEdge();

	// create map
	createMap();

	// create physic map
	//createPhysic();

	// create object
	createObject();

	// add dispathcher
	addDispatCher();

	// create joystick
	createJoystick(this);

	// update 
	scheduleUpdate();


	return true;
}

void GamePlay::update(float deltaTime)
{
	setViewPointCenter(knight->getSprite()->getPosition());
	UpdateJoystick(deltaTime);
	
	// update knight
	knight->Update(deltaTime);

	// update zombie
	for (int i = 0; i < zombies.size(); i++) {
		(zombies.at(i))->Update(deltaTime);
	}

	// update dragon
	for (int i = 0; i < dragons.size(); i++) {
		(dragons.at(i))->Update(deltaTime);
		(dragons.at(i))->startAI(knight);
	}
}

void GamePlay::createMap()
{
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("Map/map_2.tmx");
	_objectGroup = _tileMap->getObjectGroup("Object");
	_physics = _tileMap->getLayer("Physic");
	this->addChild(_tileMap);
	_physics->setVisible(false);
}

void GamePlay::createObject()
{
	int numDragon = 0;
	int numZombie = 0;
	auto objects = _objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++) {
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			knight = new Knight(this);
			knight->getSprite()->setPosition(Vec2(posX, posY));
			knight->getSprite()->setScale(0.7);
		}
		else if (type == 2) {
			Objject* dragon = new Dragon(this, numDragon);
			dragon->getSprite()->setPosition(Vec2(posX, posY));
			dragons.push_back(dragon);
			numDragon++;
		}
		else if (type == 3) {
			Objject* zombie = new Zombie(this, numZombie);
			zombie->getSprite()->setPosition(Vec2(posX, posY));
			zombies.push_back(zombie);
			numZombie++;
		}
	}
}

void GamePlay::setViewPointCenter(CCPoint position)
{
	CCSize winSize = Director::sharedDirector()->getWinSize();
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * this->_tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
	layerr->setPosition(-viewPoint); // hen xui
}

void GamePlay::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
	{
		knight->getSprite()->getPhysicsBody()->setVelocity(-Vec2(150, 0));
		knight->getSprite()->setFlippedX(true);
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		knight->getSprite()->getPhysicsBody()->setVelocity(Vec2(150, 0));
		knight->getSprite()->setFlippedX(false);
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		knight->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 150));
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		knight->getSprite()->getPhysicsBody()->setVelocity(-Vec2(0, 150));
		break;
	}
	default:
		break;
	}
}

void GamePlay::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
}

void GamePlay::addDispatCher()
{
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GamePlay::OnKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GamePlay::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	// contact
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlay::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GamePlay::createEdge()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);
}

void GamePlay::createPhysic()
{
	Size layerSize = _physics->getLayerSize();
	for (int i = 0; i < layerSize.width; i++) {
		for (int j = 0; j < layerSize.height; j++) {
			auto tileSet = _physics->getTileAt(Vec2(i, j));
			if (tileSet != NULL) {
				auto physic = PhysicsBody::createBox(tileSet->getContentSize());
				physic->setCollisionBitmask(1);
				physic->setContactTestBitmask(true);
				physic->setDynamic(false);
				tileSet->setPhysicsBody(physic);
			}
		}
	}
}

void GamePlay::Fight(Ref* sender, Widget::TouchEventType type) // co tham so ham CALLBACK ko loi
{
	((Knight*)(knight))->fight();
}

void GamePlay::Fire(Ref * sender, Widget::TouchEventType type)
{
	((Knight*)(knight))->skill();
}

bool GamePlay::onContactBegin(PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody();
	auto nodeB = contact.getShapeB()->getBody();

	// fire vs dragon
	if ((nodeA->getCollisionBitmask() == FIRE_TAG && nodeB->getCollisionBitmask() == DRAGON_TAG) || (nodeA->getCollisionBitmask() == DRAGON_TAG && nodeB->getCollisionBitmask() == FIRE_TAG)) {
		if (nodeA->getCollisionBitmask() == DRAGON_TAG) {
			dragons.at(nodeA->getGroup())->setBlood(dragons.at(nodeA->getGroup())->getBlood() - 10);
			if (dragons.at(nodeA->getGroup())->getBlood() <= 90) {
				/*auto soul = new Soul(this);
				auto moveTo = MoveTo::create(2, knight->getSprite()->getPosition());
				soul->getSprite()->setPosition(dragons.at(nodeA->getGroup())->getSprite()->getPosition());
				soul->getSprite()->runAction(moveTo);*/
			}
		}
		else if (nodeB->getCollisionBitmask() == DRAGON_TAG) {
			dragons.at(nodeB->getGroup())->setBlood(dragons.at(nodeB->getGroup())->getBlood() - 10);
			if (dragons.at(nodeB->getGroup())->getBlood() <= 90) {
				/*auto soul = new Soul(this);
				auto moveTo = MoveTo::create(2, knight->getSprite()->getPosition());
				soul->getSprite()->setPosition(dragons.at(nodeB->getGroup())->getSprite()->getPosition());
				soul->getSprite()->runAction(moveTo);*/
			}
		}
	}

	// fire vs zombie
	if ((nodeA->getCollisionBitmask() == FIRE_TAG && nodeB->getCollisionBitmask() == ZOMBIE_TAG) || (nodeA->getCollisionBitmask() == ZOMBIE_TAG && nodeB->getCollisionBitmask() == FIRE_TAG)) {
		if (nodeA->getCollisionBitmask() == ZOMBIE_TAG) {
			zombies.at(nodeA->getGroup())->setBlood(zombies.at(nodeA->getGroup())->getBlood() - 10);
		}
		else if (nodeB->getCollisionBitmask() == ZOMBIE_TAG) {
			zombies.at(nodeB->getGroup())->setBlood(zombies.at(nodeB->getGroup())->getBlood() - 10);
		}
	}


	return false;
}

void GamePlay::createJoystick(Layer* layer)
{
	auto thumb = Sprite::create("Joystick/thumb.png");
	auto joystick = Sprite::create("Joystick/joystick.png");
	Rect joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(MARGIN_JOYSTICK + thumb->getBoundingBox().size.width / 2 + joystick->getBoundingBox().size.width / 2
		, MARGIN_JOYSTICK + thumb->getBoundingBox().size.height / 2 + joystick->getBoundingBox().size.height / 2);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(Vec2(100, 100));
	joystickBase->setBackgroundSprite(thumb);
	joystickBase->setAnchorPoint(Vec2(0, 0));
	joystickBase->setThumbSprite(joystick);
	joystickBase->getThumbSprite()->setScale(0.2f);
	joystickBase->setScale(1.0f);
	joystick->setScale(0.5f);
	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(Vec2(100, 100));

	leftJoystick = joystickBase->getJoystick();
	activeRunRange = thumb->getBoundingBox().size.height / 2;

	layerr = Layer::create();
	layerr->addChild(joystickBase);

	// btn fight
	btnFight = ui::Button::create("Joystick/hammer_normal.png", "Joystick/hammer_pressed.png");
	btnFight->setPosition(Vec2(800, 100));
	btnFight->addTouchEventListener(CC_CALLBACK_2(GamePlay::Fight, this));
	layerr->addChild(btnFight);

	// btn Fire
	btnFire = ui::Button::create("Joystick/fire_normal.png", "Joystick/fire_press.png");
	btnFire->setPosition(Vec2(900, 100));
	btnFire->addTouchEventListener(CC_CALLBACK_2(GamePlay::Fire, this));
	layerr->addChild(btnFire);

	layer->addChild(layerr);
}

void GamePlay::UpdateJoystick(float dt)
{
	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		if (degree > 135 && degree < 180 || degree > -180 && degree < -135)//MoveLeft
		{
			knight->getSprite()->getPhysicsBody()->setVelocity(-Vec2(SPEED_GO, 0));
			knight->getSprite()->setFlippedX(true);
			((Knight*)(knight))->go();
		}
		if (degree > -135 && degree < -45)//Move Down
		{
			knight->getSprite()->getPhysicsBody()->setVelocity(-Vec2(0, SPEED_GO));
			((Knight*)(knight))->go();
		}
		if (degree > -45 && degree < 45)//Move Right
		{
			knight->getSprite()->getPhysicsBody()->setVelocity(Vec2(SPEED_GO, 0));
			knight->getSprite()->setFlippedX(false);
			((Knight*)(knight))->go();
		}
		if (degree > 45 && degree < 135)//Move Up
		{
			knight->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, SPEED_GO));
			((Knight*)(knight))->go();
		}
	}
	else
	{
		((Knight*)(knight))->startAI(knight);
		knight->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
}

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}
