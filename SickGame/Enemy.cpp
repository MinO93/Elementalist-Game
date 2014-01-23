#include "Enemy.h"
#include "GameFeatures.h"

#include "MemoryLeak.h"

const int GameBlockSize = 50;

static int	TextureSize_x(256/8);
static int	TextureSize_y(288/6);

static float GravityValue = 18;			//Hur högt Gubben hoppar (Oberoende hur snabbt han hoppar)
static float GravitySpeed = 200;		//Hur snabbt han hoppar och faller

static int HealthBar_x = 50;
static int HealthBar_y = 10;

static int Movmentspeed = 50;

static const int AreaCheck = 1;

Enemy::Enemy(float SpawnPosition_x, float SpawnPosition_y, Faction faction,  int Creature_Class) :
	m_faction(faction),
	m_HealthPoints(100),
	m_isAlive(true)
{
	ClassSelect(Creature_Class);
	m_physics = new Physics(sprite, this, mage->GetMovementSpeed());

	sprite.setPosition(sf::Vector2f(SpawnPosition_x+10, SpawnPosition_y+1));
	initilize();

	HealthBar.setSize(sf::Vector2f(HealthBar_x, HealthBar_y));
	HealthBar.setOrigin(sf::Vector2f());
	HealthBar.setFillColor(sf::Color(255, 0, 0, 150));

	HealthBarBlackFrame = HealthBar;

	HealthBarBlackFrame.setOutlineColor(sf::Color(0, 0, 0, 150));
	HealthBarBlackFrame.setOutlineThickness(2);
	HealthBarBlackFrame.setFillColor(sf::Color(0, 0, 0, 0));
}


Enemy::~Enemy(void)
{
	delete m_physics;
	delete mage;
}

void Enemy::initilize()
{
	EnemyTexture = mage->StandingRight();
	sprite.setTexture(*EnemyTexture);
	sprite.setOrigin(sf::Vector2f(0, 0));
	m_AnimationTimer = 0;
	m_Diraction_Right = true;
	StandardSpell.restart();
}

void Enemy::Update(float deltaTime, int PlayerPosition_x, int PlayerPosition_y)
{
	HealthBar.setPosition(sf::Vector2f((sprite.getPosition().x + TextureSize_x/2) -HealthBar_x/2, sprite.getPosition().y-20));
	HealthBar.setSize(sf::Vector2f(m_HealthPoints/2, HealthBar_y));
	HealthBarBlackFrame.setPosition(sf::Vector2f((sprite.getPosition().x + TextureSize_x/2) -HealthBar_x/2, sprite.getPosition().y-20));
	
	if(m_HealthPoints <= 0 )
	{
		m_isAlive = false;
	}
	
	if(m_physics->Get_inAir() == false && m_physics->Get_AffectedByWind() == false)
	{
		m_Diraction_Right = GameFeatures::TurnEnemyDiraction(*this, m_Diraction_Right);
	}

	if(m_physics->Get_AffectedByIce() == false && m_physics->Get_Immobilize() == false)
	{
		HealthBar.setFillColor(sf::Color(255, 0, 0, 150));	
	}

	
	m_physics->Update(deltaTime);
	CreatureMovement(deltaTime);
	Animations(deltaTime);
	Fire(PlayerPosition_x, PlayerPosition_y, TextureSize_x, TextureSize_y);
}

void Enemy::ClassSelect(int Creature_Class)
{
	if(Creature_Class == 0)
	{
		mage = new FireMage;
	}
	else if(Creature_Class == 1)
	{
		mage = new FrostMage;
	}
	else if(Creature_Class == 2)
	{
		mage = new AirMage;
	}
	else if(Creature_Class == 3)
	{
		mage = new BallEnemy;
	}
}


void Enemy::CreatureMovement(float deltaTime)
{
	m_physics->MoveDown(deltaTime);
	
	if (m_Diraction_Right == false)
	{
		//Skickar tillbaka true om den kolliderar mot väggen
		if(m_physics->MoveLeft( deltaTime ) == true)
		{
			m_Diraction_Right = !m_Diraction_Right;
		}
		m_AnimationTimer += 5000*deltaTime;
	}

	if (m_Diraction_Right == true)
	{
		//Skickar tillbaka true om den kolliderar mot väggen
		if(m_physics->MoveRight( deltaTime ) == true)
		{
			m_Diraction_Right = !m_Diraction_Right;
		}
		m_AnimationTimer += 5000*deltaTime;
	}
}



void Enemy::Animations(float deltaTime)
{
		if(		m_AnimationTimer < 500	&& m_Diraction_Right == false)	{ EnemyTexture = mage->RunningLeft1(); }
		else if(m_AnimationTimer < 1000	&& m_Diraction_Right == false)	{ EnemyTexture = mage->StandingLeft(); }
		else if(m_AnimationTimer < 1500	&& m_Diraction_Right == false)	{ EnemyTexture = mage->RunningLeft2(); }
		else if(m_AnimationTimer < 2000	&& m_Diraction_Right == false)	{ EnemyTexture = mage->StandingLeft(); }
		
		if(		m_AnimationTimer < 500 	&& m_Diraction_Right == true) { EnemyTexture = mage->RunningRight1(); }
		else if(m_AnimationTimer < 1000	&& m_Diraction_Right == true) { EnemyTexture = mage->StandingRight(); }
		else if(m_AnimationTimer < 1500	&& m_Diraction_Right == true) { EnemyTexture = mage->RunningRight2(); }
		else if(m_AnimationTimer < 2000	&& m_Diraction_Right == true) { EnemyTexture = mage->StandingRight(); }

		if(m_AnimationTimer > 2500)	{ m_AnimationTimer = 0; }
	

		sprite.setTexture(*EnemyTexture);
}

void Enemy::Fire(int PlayerPosition_x,  int PlayerPosition_y,  int PlayerTextureSize_x,  int PlayerTextureSize_y)
{
	bool PlayerIsClose = false;
	int StandardSpellRange = mage->GetStandardSpellRange();

	if(m_Diraction_Right == true)
	{
		PlayerIsClose = GameFeatures::Collision(PlayerPosition_x, PlayerPosition_y, PlayerTextureSize_x , PlayerTextureSize_y,
					GetPosition_x(), GetPosition_y(), GetTextureSize_x()+StandardSpellRange, GetTextureSize_y());
	}
	else if(m_Diraction_Right == false)
	{
		PlayerIsClose = GameFeatures::Collision(PlayerPosition_x, PlayerPosition_y, PlayerTextureSize_x , PlayerTextureSize_y,
					GetPosition_x()-StandardSpellRange, GetPosition_y(), GetTextureSize_x()+StandardSpellRange, GetTextureSize_y());
	}

	sf::Time timer = StandardSpell.getElapsedTime();

	if (timer.asSeconds() > 0.5 && PlayerIsClose == true && m_physics->Get_inAir() == false)
	{
		StandardSpell.restart();
		mage->StandardSpell(m_Diraction_Right, GetPosition_x(), GetPosition_y(), m_faction);
	}
}

void Enemy::ReceiveDamage(int damage)
{
	if(m_physics->Get_AffectedByIce() == true)
	{
		m_HealthPoints -= damage * 2;
	}
	else
	{
		m_HealthPoints -= damage;
	}
}

		//Alla Spell-Påverkande effecter
		void Enemy::GetHitByWind(int windspeed)
		{
			m_physics->GetHitByWind(windspeed);
		}

		void Enemy::GetHitByIce(int ElementPower)
		{
			m_physics->GetHitByIce(ElementPower);
			HealthBar.setFillColor(sf::Color(0, 0, 255, 150));
		}


// Alla Get Funktioner
float Enemy::GetPosition_x()const
{
	return sprite.getPosition().x;
}

float Enemy::GetPosition_y()const
{
	return sprite.getPosition().y;
}

int Enemy::GetTextureSize_x()const
{
	return mage->GetTextureSize_x();
}

int Enemy::GetTextureSize_y()const
{
	return mage->GetTextureSize_y();
}

bool Enemy::GetDiraction_Right()const
{
	return m_Diraction_Right;
}

Element Enemy::GetElement()const
{
	return mage->GetElement();
}

bool Enemy::IsAlive()const
{
	return m_isAlive;
}
