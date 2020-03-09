#pragma once
#include "Objject.h"
class CountTime : public Objject
{
private:
	int timeRemain;
	Layer* layer;
	Label* labelTimer;
public:
	void Init();
	void Update(float deltaTime);
	void startAI(Objject* knight);
	CountTime(Layer* layer, int timeRemain);
	~CountTime();
};

