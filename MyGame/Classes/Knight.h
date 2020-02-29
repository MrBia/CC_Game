#pragma once
#include "Objject.h"

enum state {
	START,
	GO,
	RUN,
	FIGHT,
	K_SKILL
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
	cocos2d::ui::LoadingBar* bloodbg;
	cocos2d::ui::LoadingBar* blood;
public:
	void Init();
	void Update(float deltaTime);
	Knight(Layer* layer);
	void startAI(Objject* knight);
	void fight();
	void skill();
	void go();
	void run();
	void setState(int nextState);
	void createBloodBar();

	~Knight();
};