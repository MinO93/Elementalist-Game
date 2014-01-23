#pragma once
#include <SFML\Graphics\Texture.hpp>
#include "AbilityObjekt.h"


class Class
{
public:

	virtual ~Class(void){};
	virtual sf::Texture * StandingLeft()const = 0;
	virtual sf::Texture * RunningLeft1()const = 0;
	virtual sf::Texture * RunningLeft2()const = 0;
	virtual sf::Texture * StandingRight()const = 0;
	virtual sf::Texture * RunningRight1()const = 0;
	virtual sf::Texture * RunningRight2()const = 0;
	virtual Element GetElement()const = 0;
	virtual int GetTextureSize_x()const = 0;
	virtual int GetTextureSize_y()const = 0;
	virtual int GetStandardSpellRange()const = 0;
	virtual int GetMovementSpeed()const = 0;
	

	virtual void StandardSpell(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) = 0;
	virtual void SpecialAbility(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) = 0;
};

