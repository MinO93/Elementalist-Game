#pragma once
#include "Creature.h"
#include "FrostMage.h"
#include "AirMage.h"
#include "FireMage.h"
#include <vector>
#include <SFML\Audio.hpp>


class Player : public Creature, public sf::Drawable
{
public:
	Player(int spelare);
	~Player(void);

	static void LoadSound();

	void initilize();
	virtual void SetPosition(float position_x, float position_y);
	void Update(float deltaTime);
	void Animations(float deltaTime);
	void Fire();
	void ChangeMageSpecialiaztion();

	void SetJumpOff();

	//Movement Funktion
	void PlayerMovement(float deltaTime);
	
	//Alla Spell-Påverkande effecter
	virtual void ReceiveDamage(int damage);
	void GetHitByWind(int windspeed);
	void GetHitByIce(int ElementPower);
	

	// Alla Get Funktioner
	float GetPosition_x()const;
	float GetPosition_y()const;
	int GetTextureSize_x()const;
	int GetTextureSize_y()const;
	bool IsAlive()const;
	
private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, PlayerTexture);
		target.draw(HealthBar, states);
		target.draw(HealthBarBlackFrame, states);
		target.draw(SpecialAbilityBar, states);
		target.draw(SpecialAbilityBarBlackFrame, states);
    }

	int m_JoyStickPlayer;
	float m_Joystick_x_value;
	float m_Joystick_Z_value;
	bool m_WasPress_ChangeMage;
	bool m_WasPress_StandardJump;
	bool m_WasPress_SpecialAbility;

	Class* mage[3];
	Physics * m_physics;
	int MageSpecialiaztionIndex;
	sf::Texture * PlayerTexture;
	sf::Sprite sprite;
	sf::RectangleShape HealthBar;
	sf::RectangleShape HealthBarBlackFrame;
	sf::RectangleShape SpecialAbilityBar;
	sf::RectangleShape SpecialAbilityBarBlackFrame;
	Faction faction;
	
	sf::Clock C_StandardSpell;
	float m_SpecialAbility_timer;

	float m_SpawnPosition_x;
	float m_SpawnPosition_y;

	float m_AnimationTimer;

	int m_HealthPoints;
	bool m_Diraction_Right;
	bool m_IsAlive;
};

