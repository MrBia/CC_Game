#pragma once
#include "Objject.h"

class Soul : public Objject
{
private:
	Layer* layer;
public:
	void startAI(Objject* knight);
	void Init();
	void Update(float deltaTime);
	Soul(Layer* layer);
	~Soul();
};

