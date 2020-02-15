#pragma once
#include "define.h"
#include "cocos2d.h"

USING_NS_CC;
class Objject
{
private:
	int blood;
	Sprite* sprite;
public:
	void setBlood(int blood);
	int getBlood();
	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	Objject();
	~Objject();
};

