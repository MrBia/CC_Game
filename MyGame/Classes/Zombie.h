#pragma once
#include "Objject.h"

enum stateZombie {
	Z_START,
	NORMAL_FIGHT,
	SKILL_FIGHT,
	DIE
};

class Zombie : public Objject
{
private:
	Layer* layer;
	Animate* animationFight_1;
	Animate* animationFight_2;
	Animate* animationDie;
	int currentState;
	int index;
	cocos2d::ui::LoadingBar* bloodbg;
	cocos2d::ui::LoadingBar* blood;
public:
	void Init();
	void Update(float deltaTime);
	void start();
	void normalFight();
	void skillFight();
	void die();
	void setState(int nextState);
	void createBloodBar();
	Zombie(Layer* layer, int index);
	~Zombie();
};

