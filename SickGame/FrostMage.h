#pragma once
#include "Class.h"
#include "IceBolt.h"
#include <SFML\Graphics.hpp>

class FrostMage : public Class
{
public:
	FrostMage(void);
	~FrostMage(void);
	virtual sf::Texture * StandingLeft()const;
	virtual sf::Texture * RunningLeft1()const;
	virtual sf::Texture * RunningLeft2()const;
	virtual sf::Texture * StandingRight()const;
	virtual sf::Texture * RunningRight1()const;
	virtual sf::Texture * RunningRight2()const;
	virtual Element	GetElement()const;
	virtual int GetTextureSize_x()const;
	virtual int GetTextureSize_y()const;
	virtual int GetStandardSpellRange()const;
	virtual int GetMovementSpeed()const;

	virtual void StandardSpell(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction);
	virtual void SpecialAbility(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction);
	static void LoadImage();
	static void CloseImage();

};

