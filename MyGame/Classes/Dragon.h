#pragma once
#include "Objject.h"

enum stateDragon {
	D_START,
	FIRE_UP,
	FIRE_DOWN_NORMAL,
	FIRE_DOWN_SKILL,
	FLY,
	D_DIE
};

class Dragon :
	public Objject
{
private:
	Layer* layer;
	Animate* animateStart;
	Animate* animateFireUp;
	Animate* animateFireDownNormal;
	Animate* animateFireDownSkill;
	Animate* animateFly;
	Animate* animateDie;
	int  currentState;
public:
	void Init();
	void Update(float deltaTime);
	void setState(int nextState);
	void start();
	void fireUp();
	void fireDownNormal();
	void fireDownSkill();
	void fly();
	void die();
	Dragon(Layer* layer);
	~Dragon();
};

