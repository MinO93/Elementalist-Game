#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Sprite.hpp>

class Creature;

#pragma once
class Physics
{
public:
	Physics(sf::Sprite &sprite, Creature *creature, float MovementSpeed);
	~Physics(void);

	void ResetValues();
	void Update(float deltaTime);

	// Vanliga MoveFunktioner
	bool MoveRight(float deltaTime);
	bool MoveLeft(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveUp(float deltaTime);
	void Jump(float deltaTime);
	void SetJumpOff();
	void MoveByWind(float deltaTime);

	// GetHitBy Funktioner
	void GetHitByWind(int WindSpeed);
	void GetHitByIce(int ElementPower);

	// Get Funktioner
	bool Get_AffectedByWind();
	bool Get_AffectedByIce();
	bool Get_Immobilize();
	bool Get_inAir();

private:

	sf::Sprite * users_sprite;
	Creature  * users_Creature;

	// Wind Affected variablar
	bool	m_AffectedByWind;
	float	m_WindSpeed_x;
	bool	m_WindDiraction_Right;

	// Ice
	float	m_AffectedByIce_Timer;
	bool	m_AffectedByIce;
	float	m_SlowPower;

	// immobilize variablar
	bool m_immobilize;
	float m_immobilize_Timer;


	// Movement Variabler
	float	m_LastMove_x;
	float	m_LastMove_y;
	float	m_Acceleration_y;
	float	m_Acceleration_x;
	float	m_MovementSpeed;

	// Gravity/Jump Variabler
	bool	m_inAir;
	bool	m_JumpOn;
	float	m_JumpTimer;
};

