#pragma once
#include "C:\Users\Admin\Desktop\CC_Game\MyGame\cocos2d\cocos\2d\CCScene.h"
#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "Objject.h"
#include "Knight.h"
#include "Zombie.h"
#include "Dragon.h"
#include "ui\UIButton.h"
#include "Soul.h"
#include "CountTime.h"

#define MARGIN_JOYSTICK 50

USING_NS_CC;
using namespace ui;
class GamePlay : public Layer
{
private:
	// map
	CCTMXTiledMap* _tileMap;
	CCTMXLayer* _background;
	CCTMXLayer* _object;
	CCTMXObjectGroup *_objectGroup;
	CCTMXLayer* _physics;
	Sprite* sprite;
	SneakyJoystickSkinnedBase* joystickBase;
	SneakyJoystick *leftJoystick;
	float activeRunRange;

	// object
	Objject* knight;
	Objject* zombie;
	std::vector<Objject*> zombies;
	Objject * dragon;
	std::vector<Objject*> dragons;

	// joystick
	Layer* layerr;
	ui::Button* btnFight;
	ui::Button* btnFire;
public:
	static Scene* createGame();
	virtual bool init();
	void update(float deltaTime);
	void createMap();
	void createObject();
	void setViewPointCenter(CCPoint position);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);	
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void addDispatCher();
	void createEdge();
	void createPhysic();
	void Fight(Ref* sender, Widget::TouchEventType type);
	void Fire(Ref* sender, Widget::TouchEventType type);
	bool onContactBegin(PhysicsContact& contact);
	void createJoystick(Layer* layer);
	void UpdateJoystick(float dt);
	GamePlay();
	~GamePlay();
	CREATE_FUNC(GamePlay);
};

