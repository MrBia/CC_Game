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
	Animate* animationStart;
	int currentState;
	int index;
	cocos2d::ui::LoadingBar* bloodbg;
	cocos2d::ui::LoadingBar* blood;
	bool life = true;
public:
	void Init();
	void Update(float deltaTime);
	void startAI(Objject* knight);
	void normalFight();
	void skillFight();
	void die();
	void setState(int nextState);
	void createBloodBar();
	float distance(Objject* zombie, Objject* knight);

	Zombie(Layer* layer, int index);
	~Zombie();
};

