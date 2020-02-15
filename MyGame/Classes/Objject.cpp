#include "Objject.h"



void Objject::setBlood(int blood)
{
	this->blood = blood;
}

int Objject::getBlood()
{
	return this->blood;
}

void Objject::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

Sprite * Objject::getSprite()
{
	return this->sprite;
}

Objject::Objject()
{
}


Objject::~Objject()
{
}
