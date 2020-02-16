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
	((Zombie*)(zombie))->normalFight();
	((Dragon*)(dragon))->die();
}

void GamePlay::createMap()
{
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("Map/map_2.tmx");
	_objectGroup = _tileMap->getObjectGroup("Object");
	this->addChild(_tileMap);
}

void GamePlay::createObject()
{
	/*knight = new Knight(this);
	zombie = new Zombie(this);
	dragon = new Dragon(this);
	((Zombie*)(zombie))->normalFight();
	((Knight*)(main))->start();*/

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
		}
		else if (type == 2) {
			dragon = new Dragon(this);
			dragon->getSprite()->setPosition(Vec2(posX, posY));
		}
		else if (type == 3) {
			zombie = new Zombie(this);
			zombie->getSprite()->setPosition(Vec2(posX, posY));
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

void GamePlay::Fight(Ref* sender, Widget::TouchEventType type) // co tham so ham CALLBACK ko loi
{
	((Knight*)(knight))->fight();
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
		((Knight*)(knight))->start();
		knight->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
}

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}
