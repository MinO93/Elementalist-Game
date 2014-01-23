#pragma once
#include <SFML\Graphics.hpp>
#include "Level.h"
#include "AbilityObjekt.h"
#include "Physics.h"


class Creature 
{
public:
	Creature(void);
	virtual ~Creature(void);
	virtual float GetPosition_y()const = 0;
	virtual float GetPosition_x()const = 0;
	virtual void ReceiveDamage(int damage) = 0;
	virtual int GetTextureSize_x()const = 0;
	virtual int GetTextureSize_y()const = 0;

};

