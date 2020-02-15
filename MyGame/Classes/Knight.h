#pragma once
#include "Objject.h"

enum state {
	START,
	GO,
	RUN,
	FIGHT
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
	int currentState;
public:
	void Init();
	void Update(float deltaTime);
	Knight(Layer* layer);
	void start();
	void fight();
	void go();
	void run();
	void setState(int nextState);

	~Knight();
};