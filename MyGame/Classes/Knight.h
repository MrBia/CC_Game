#pragma once
#include "Objject.h"

enum state {
	START,
	GO,
	RUN,
	FIGHT,
	K_SKILL,
	K_DIE
};

class Knight :
	public Objject
{
private:
	Layer* layer;
	Animate* aniFight;
	Animate* aniGo;
	Animate* aniRun;
	Animate* aniWait;
	Animate* aniFire;
	int currentState;
	Sprite* fire;
	Sprite* fight_damage;
	cocos2d::ui::LoadingBar* bloodbg;
	cocos2d::ui::LoadingBar* blood;
	bool isLeft = false;
	MoveBy* moveBy;
	MoveBy* moveBy_fight_damage;
	int damaged;
	bool life = true;
	int totalMoney;
public:
	void Init();
	void Update(float deltaTime);
	Knight(Layer* layer);
	void startAI(Objject* knight);
	void fight();
	void skill();
	void go();
	void run();
	void die();
	void setState(int nextState);
	void createBloodBar();
	void IsLeft(bool isLeft);
	void setMoney(int money);
	int getMoney();

	~Knight();
};