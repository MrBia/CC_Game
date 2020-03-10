#pragma once
#include "Objject.h"
class CountTime : public Objject
{
private:
	int timeRemain;
	Layer* layer;
	Label* labelTimer;
	Vec2 pos;
	Size size;
public:
	void Init();
	void Update(float deltaTime);
	void startAI(Objject* knight);
	int getTimeRemain();
	CountTime(Layer* layer, int timeRemain, Vec2 pos, Size size);
	~CountTime();
};

