#include "FireBolt.h"

#include "MemoryLeak.h"

static sf::Texture * T_FireBoltLeft[3]	= {NULL, NULL, NULL};

static sf::Texture * T_FireBoltRight[3]	= {NULL, NULL, NULL};


static Element element = FIRE;
static int DAMAGE = 25;
static int SPEED = 500;
static int RANGE = 300;
static int ELEMENTPOWER = 100;

static int	TextureSize_x(26);
static int	TextureSize_y(26);


FireBolt::FireBolt(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) : 
	m_Speed(Diraction(Diraction_Right)),
	m_RangeLeft(RANGE),
	m_AnimationTimer(0),
	m_isAlive(true),
	m_Texture(T_FireBoltRight[0]),
	m_faction(faction)
{
	m_Sprite.setTexture(*m_Texture);
	m_Sprite.setPosition(sf::Vector2f(Owners_Position_x, Owners_Position_y));
}

FireBolt::~FireBolt(void)
{
}

//Denna funktion är Static
void FireBolt::LoadImage()
{
	T_FireBoltLeft[0] = new sf::Texture;
	T_FireBoltLeft[1] = new sf::Texture;
	T_FireBoltLeft[2] = new sf::Texture;

	T_FireBoltRight[0] = new sf::Texture;
	T_FireBoltRight[1] = new sf::Texture;
	T_FireBoltRight[2] = new sf::Texture;

	if (!T_FireBoltLeft[0]->loadFromFile("Pictures/FireBall.png", sf::IntRect(TextureSize_x*0, TextureSize_y*1, TextureSize_x, TextureSize_y))){}
	if (!T_FireBoltLeft[1]->loadFromFile("Pictures/FireBall.png", sf::IntRect(TextureSize_x*1, TextureSize_y*1, TextureSize_x, TextureSize_y))){}
	if (!T_FireBoltLeft[2]->loadFromFile("Pictures/FireBall.png", sf::IntRect(TextureSize_x*2, TextureSize_y*1, TextureSize_x, TextureSize_y))){}

	if (!T_FireBoltRight[0]->loadFromFile("Pictures/FireBall.png", sf::IntRect(TextureSize_x*0, TextureSize_y*2, TextureSize_x, TextureSize_y))){}
	if (!T_FireBoltRight[1]->loadFromFile("Pictures/FireBall.png", sf::IntRect(TextureSize_x*1, TextureSize_y*2, TextureSize_x, TextureSize_y))){}
	if (!T_FireBoltRight[2]->loadFromFile("Pictures/FireBall.png", sf::IntRect(TextureSize_x*2, TextureSize_y*2, TextureSize_x, TextureSize_y))){}
}

//Denna funktion är Static
void FireBolt::CloseImage()
{
	delete T_FireBoltLeft[0];
	delete T_FireBoltLeft[1];
	delete T_FireBoltLeft[2];

	delete T_FireBoltRight[0];
	delete T_FireBoltRight[1];
	delete T_FireBoltRight[2];
}

void FireBolt::Update(float deltaTime)
{
	m_RangeLeft -=  SPEED* deltaTime ;
	if(m_RangeLeft < 0)
	{
		m_isAlive = false;
	}

	if(m_RangeLeft < 15)
	{
		m_Sprite.setColor(sf::Color(255, 255, 255, 50));
	}
	else if(m_RangeLeft < 30)
	{
		m_Sprite.setColor(sf::Color(255, 255, 255, 100));
	}
	else if(m_RangeLeft < 45)
	{
		m_Sprite.setColor(sf::Color(255, 255, 255, 150));
	}
	else if(m_RangeLeft < 60)
	{
		m_Sprite.setColor(sf::Color(255, 255, 255, 200));
	}


	if( GameFeatures::Check_Collision_With_StandardBlocks(this) )
	{
		m_isAlive = false;
	}

	GameFeatures::DamageDealerFunction(this);
	Movement(deltaTime);
	Animations(deltaTime);
}

int FireBolt::Diraction(bool DiractionRight)
{
	if(DiractionRight)
	{
		return SPEED;
	}
	else if(!DiractionRight)
	{
		return -SPEED;
	}	
}


void FireBolt::Animations(float deltaTime)
{

	if(m_Speed > 0)
	{
		if(		m_AnimationTimer < 500)		{ m_Texture = T_FireBoltRight[0]; }
		else if(m_AnimationTimer < 1000)	{ m_Texture = T_FireBoltRight[1]; }
		else if(m_AnimationTimer < 1500)	{ m_Texture = T_FireBoltRight[2]; }
	}

	if(m_Speed < 0)
	{
		if(		m_AnimationTimer < 500)		{ m_Texture = T_FireBoltLeft[0]; }
		else if(m_AnimationTimer < 1000)	{ m_Texture = T_FireBoltLeft[1]; }
		else if(m_AnimationTimer < 1500)	{ m_Texture = T_FireBoltLeft[2]; }
	}

		if(m_AnimationTimer > 2000)	{ m_AnimationTimer = 0; }
	
		m_AnimationTimer += 5000*deltaTime;

		m_Sprite.setTexture(*m_Texture);
}

void FireBolt::Movement(float deltaTime)
{
    m_Sprite.move(m_Speed*deltaTime, 0);
}

bool FireBolt::IsAlive()
{
	return m_isAlive;
}

void FireBolt::KillObjekt()
{
	m_isAlive = false;
}

int FireBolt::GetPosition_x()const
{
	return m_Sprite.getPosition().x;
}

int FireBolt::GetPosition_y()const
{
	return m_Sprite.getPosition().y;
}

int FireBolt::GetTextureSize_x()const
{
	return TextureSize_x;
}

int FireBolt::GetTextureSize_y()const
{
	return TextureSize_y;
}

int FireBolt::GetDamage()const
{
	return DAMAGE;
}

Element FireBolt::GetElement()const
{
	return element;
}

Faction FireBolt::GetFaction()const
{
	return m_faction;
}

int FireBolt::GetSpeed()const
{
	return m_Speed;
}

int FireBolt::GetRange()
{
	return RANGE;
}

int FireBolt::GetElementPower()const
{
	return ELEMENTPOWER;
}