#pragma once
#include "GameFeatures.h"

class IceBolt : public AbilityObjekt
{
public:
	IceBolt(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction);
	~IceBolt(void);
	static void LoadImage();
	static void CloseImage();
	virtual void Update(float deltaTime);
	int Diraction(bool DiractionRight);
	void Animations(float deltaTime);
	void Movement(float deltaTime);
	virtual bool IsAlive();
	virtual void KillObjekt();
	virtual int GetPosition_x()const;
	virtual int GetPosition_y()const;
	virtual int GetTextureSize_x()const;
	virtual int GetTextureSize_y()const;
	virtual int GetDamage()const;
	virtual Element GetElement()const;
	virtual Faction GetFaction()const;
	virtual int GetSpeed()const;
	virtual int GetElementPower()const;
	static int GetRange();
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_Sprite, m_Texture);
    }

	sf::Texture * m_Texture;
	sf::Sprite m_Sprite;
	Faction m_faction;
	int m_AnimationTimer;
	int m_Damage;
	int m_Speed;
	float m_RangeLeft;
	int m_Manacost;
	bool m_isAlive;

};

