#pragma once

#include "Creature.h"
#include <SFML\Graphics.hpp>
#include "FrostMage.h"
#include "AirMage.h"
#include "FireMage.h"
#include "BallEnemy.h"
#include <vector>


class Enemy : public Creature, public sf::Drawable
{
public:
	Enemy(float SpawnPosition_x, float SpawnPosition_y, Faction faction, int Creature_Class);
	~Enemy(void);

	void initilize();
	void Update(float deltaTime, int PlayerPosition_x, int PlayerPosition_y );
	void Animations(float deltaTime);
	void Fire(int PlayerPosition_x,  int PlayerPosition_y,  int PlayerTextureSize_x,  int PlayerTextureSize_y);
	void ClassSelect(int Creature_Class);

	//Movement Funktion
	void CreatureMovement(float deltaTime);
	void TurnEnemyDiraction(Level *Map);

	//Alla Spell-Påverkande effecter
	void GetHitByWind(int windspeed);
	void GetHitByIce(int ElementPower);
	virtual void ReceiveDamage(int damage);

	// Alla Get Funktioner
	float GetPosition_x()const;
	float GetPosition_y()const;
	int GetTextureSize_x()const;
	int GetTextureSize_y()const;
	bool GetDiraction_Right()const;
	Element GetElement()const;
	bool IsAlive()const;
	bool IsJumpOn( ) const;

private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, EnemyTexture);
		target.draw(HealthBar, states);
		target.draw(HealthBarBlackFrame, states);
    }


	Class* mage;
	Physics * m_physics;
	sf::Texture * EnemyTexture;
	sf::Sprite sprite;
	sf::Clock StandardSpell;
	sf::Clock StunClock;
	sf::Clock c_AffectedByIce;

	Faction m_faction;

	sf::RectangleShape HealthBar;
	sf::RectangleShape HealthBarBlackFrame;

	float m_AnimationTimer;

	float m_LastMove_x;
	float m_LastMove_y;

	bool m_Diraction_Right;
	int m_HealthPoints;
	int m_isAlive;

};

