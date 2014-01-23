#include "Physics.h"
#include "GameFeatures.h"
#include "Creature.h"

#include "MemoryLeak.h"

static float GravityValue = 18 * 1.1;		//Hur högt Gubben hoppar (Oberoende hur snabbt han hoppar)
static float GravitySpeed = 200 * 1.1;		//Hur snabbt han hoppar och faller

static const float StandardSlowPower = 0.3;

Physics::Physics(sf::Sprite &sprite, Creature *creature, float MovementSpeed) :
	users_sprite(&sprite),
	users_Creature(creature),
	m_MovementSpeed(MovementSpeed),
	m_AffectedByIce(false),
	m_AffectedByWind(false),
	m_JumpOn(false),
	m_inAir(false),
	m_Acceleration_x(0),
	m_Acceleration_y(-1),
	m_JumpTimer(0),
	m_SlowPower(StandardSlowPower),
	m_immobilize(false),
	m_immobilize_Timer(0)
{
}


Physics::~Physics(void)
{
}

void Physics::ResetValues()
{
	m_AffectedByIce		= false;
	m_AffectedByWind	= false;
	m_JumpOn			= false;
	m_inAir				= false;
	m_Acceleration_x	= 0;
	m_Acceleration_y	= -1;
	m_JumpTimer			= 0;
	m_SlowPower			= StandardSlowPower;
	m_immobilize		= false;
	m_immobilize_Timer	= 0;
	m_JumpDelay			= 0;

}

void Physics::Update( float deltaTime)
{
	m_AffectedByIce_Timer	-= deltaTime;
	m_immobilize_Timer		-= deltaTime;
	m_JumpDelay				-= deltaTime;

	if(m_AffectedByIce_Timer < 0)
	{
		m_AffectedByIce = false;
	}
		
	if(m_immobilize_Timer < 0)
	{
		m_immobilize = false;
	}

	
	MoveByWind(deltaTime);

}

bool Physics::MoveRight( float deltaTime)
{
	if(m_AffectedByWind == false && m_immobilize == false)
	{
		m_LastMove_x = m_MovementSpeed*deltaTime;
		if(m_AffectedByIce == true){ m_LastMove_x *= m_SlowPower; }
		users_sprite->move(m_LastMove_x, 0);
	}

	if(GameFeatures::Check_Collision_With_StandardBlocks(*users_Creature) == true)
	{
		users_sprite->move(-m_LastMove_x, 0);
		return true;
	}
	return false;
}

bool Physics::MoveLeft(float deltaTime)
{

	if(m_AffectedByWind == false && m_immobilize == false)
	{
		// Normal Movement
		m_LastMove_x = -m_MovementSpeed*deltaTime;
		if(m_AffectedByIce == true){ m_LastMove_x *= m_SlowPower; }
		users_sprite->move(m_LastMove_x, 0);

		if(GameFeatures::Check_Collision_With_StandardBlocks(*users_Creature) == true)
		{
			users_sprite->move(-m_LastMove_x, 0);
			return true;
		}
	}
	return false;
}

void Physics::MoveDown(float deltaTime)
{
	m_inAir = true;
	
	if(m_JumpTimer > GravityValue/GravitySpeed)
	{
	 	m_Acceleration_y -= 1;
		m_JumpTimer = 0;
 	}

	m_JumpTimer += deltaTime;
	m_LastMove_y = -GravitySpeed*deltaTime*m_Acceleration_y;
	users_sprite->move(0.0, m_LastMove_y);


	//Detta händer om spelaren kolliderar
	if( GameFeatures::Check_Collision_With_StandardBlocks(*users_Creature) )
	{
		if(m_JumpOn == false)
		{
			m_inAir = false;
		}

		// Om Spelaren hoppar och kolliderar med taket dirrekt ska hoppet få en delay till nästa hopp
		// När m_Acceleration_y == 3 händer bara när spelaren är mellan 2 ståbart block, på Y-axeln
		if(m_Acceleration_y == 3)
		{
			m_JumpDelay = 1;
		}

		users_sprite->move(0, -m_LastMove_y);

		// Ressettar Hopp/Fall-Accelerationen
		m_JumpTimer = 0;
		m_Acceleration_y = -1;
		m_JumpOn = false;
	}

}

bool Physics::bool_StandardJump(float deltaTime )
{
	if( m_inAir == false && m_JumpDelay < 0 )
	{
		// Sätter Accelerationen till 3 eller 2 för att få en uppåt rörelse
		if(m_AffectedByIce == false)
		{
			m_Acceleration_y = 3;
		}
		else if(m_AffectedByIce == true)
		{
			m_Acceleration_y = 2;
		}
		m_JumpOn = true;
		m_JumpDelay = 0.2;
		return true;
	}
	return false;
}

void Physics::SetJumpOff()
{
	m_JumpTimer = 0;
	m_Acceleration_y = -1;
	m_JumpOn = false;
}

void Physics::MoveByWind(float deltaTime)
{
	if(m_AffectedByWind == true)
	{
		m_WindSpeed_x += deltaTime;

		if(m_WindSpeed_x > GravityValue/GravitySpeed)
		{
			m_Acceleration_x -= 1;
			m_WindSpeed_x = 0;
		}

		// får inte vara mindre än -1
		if (m_Acceleration_x == -1)
		{
			m_AffectedByWind = false;
		} 

		if(m_WindDiraction_Right == false)
		{
			m_LastMove_x = -GravitySpeed*deltaTime*m_Acceleration_x;
			users_sprite->move(m_LastMove_x, 0.0);
		}
		else if(m_WindDiraction_Right == true)
		{
			m_LastMove_x = GravitySpeed*deltaTime*m_Acceleration_x;
			users_sprite->move(m_LastMove_x, 0.0);
		}

		if(GameFeatures::Check_Collision_With_StandardBlocks(*users_Creature) == true)
		{
			users_sprite->move(-m_LastMove_x, 0);
		//	m_AffectedByWind = false;
		}
	}
}


void Physics::GetHitByWind(int WindSpeed)
{
	if(WindSpeed > 0)
	{
		m_WindDiraction_Right = true;
	}
	else
	{
		m_WindDiraction_Right = false;
	}

	m_AffectedByWind = true;
	m_Acceleration_x = 3;
	m_WindSpeed_x = 0;
}

void Physics::GetHitByIce(int ElementPower)
{
	if(ElementPower >= 100)
	{
		m_immobilize_Timer = 0.5;
		m_immobilize = true;

		m_AffectedByIce_Timer = 1.7;
		m_AffectedByIce = true;
	}
	else
	{
		m_AffectedByIce_Timer = 3;
		m_AffectedByIce = true;
	}
}

bool Physics::Get_AffectedByWind()
{
	return m_AffectedByWind;
}

bool Physics::Get_AffectedByIce()
{
	return m_AffectedByIce;
}

bool Physics::Get_Immobilize()
{
	return m_immobilize;
}

bool Physics::Get_inAir()
{
	return m_inAir;
}