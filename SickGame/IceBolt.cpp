#include "IceBolt.h"

#include "MemoryLeak.h"

static sf::Texture * T_IceBoltLeft[3]	= {NULL, NULL, NULL};

static sf::Texture * T_IceBoltRight[3]	= {NULL, NULL, NULL};


static Element element = ICE;
static int DAMAGE = 0;
static int SPEED = 500;
static int RANGE = 400;
static int ELEMENTPOWER = 80;

static int	TextureSize_x(60);
static int	TextureSize_y(16);




IceBolt::IceBolt(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) : 
	m_Speed(Diraction(Diraction_Right)),
	m_RangeLeft(RANGE),
	m_AnimationTimer(0),
	m_isAlive(true),
	m_Texture(T_IceBoltRight[0]),
	m_faction(faction)
{
	m_Sprite.setTexture(*m_Texture);
	m_Sprite.setPosition(sf::Vector2f(Owners_Position_x, Owners_Position_y));
}

IceBolt::~IceBolt(void)
{
}

//Denna funktion är Static
void IceBolt::LoadImage()
{
	T_IceBoltLeft[0] = new sf::Texture;
	T_IceBoltLeft[1] = new sf::Texture;
	T_IceBoltLeft[2] = new sf::Texture;

	T_IceBoltRight[0] = new sf::Texture;
	T_IceBoltRight[1] = new sf::Texture;
	T_IceBoltRight[2] = new sf::Texture;

	T_IceBoltLeft[0]->loadFromFile("Pictures/IceBolt.png", sf::IntRect(TextureSize_x*1, TextureSize_y*0, TextureSize_x, TextureSize_y));
	T_IceBoltLeft[1]->loadFromFile("Pictures/IceBolt.png", sf::IntRect(TextureSize_x*1, TextureSize_y*1, TextureSize_x, TextureSize_y));
	T_IceBoltLeft[2]->loadFromFile("Pictures/IceBolt.png", sf::IntRect(TextureSize_x*1, TextureSize_y*2, TextureSize_x, TextureSize_y));

	T_IceBoltRight[0]->loadFromFile("Pictures/IceBolt.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, TextureSize_x, TextureSize_y));
	T_IceBoltRight[1]->loadFromFile("Pictures/IceBolt.png", sf::IntRect(TextureSize_x*0, TextureSize_y*1, TextureSize_x, TextureSize_y));
	T_IceBoltRight[2]->loadFromFile("Pictures/IceBolt.png", sf::IntRect(TextureSize_x*0, TextureSize_y*2, TextureSize_x, TextureSize_y));
}

//Denna funktion är Static
void IceBolt::CloseImage()
{
	delete T_IceBoltLeft[0];
	delete T_IceBoltLeft[1];
	delete T_IceBoltLeft[2];

	delete T_IceBoltRight[0];
	delete T_IceBoltRight[1];
	delete T_IceBoltRight[2];
}

void IceBolt::Update(float deltaTime)
{
	m_RangeLeft -=  SPEED* deltaTime ;
	if(m_RangeLeft < 0)
	{
		m_isAlive = false;
	}

	if( GameFeatures::Check_Collision_With_StandardBlocks(this) )
	{
		m_isAlive = false;
	}

	GameFeatures::DamageDealerFunction(this);
	Movement(deltaTime);
	Animations(deltaTime);
}

int IceBolt::Diraction(bool DiractionRight)
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


void IceBolt::Animations(float deltaTime)
{

	if(m_Speed > 0)
	{
		if(		m_AnimationTimer < 500)		{ m_Texture = T_IceBoltRight[0]; }
		else if(m_AnimationTimer < 1000)	{ m_Texture = T_IceBoltRight[1]; }
		else if(m_AnimationTimer < 1500)	{ m_Texture = T_IceBoltRight[2]; }
	}

	if(m_Speed < 0)
	{
		if(		m_AnimationTimer < 500)		{ m_Texture = T_IceBoltLeft[0]; }
		else if(m_AnimationTimer < 1000)	{ m_Texture = T_IceBoltLeft[1]; }
		else if(m_AnimationTimer < 1500)	{ m_Texture = T_IceBoltLeft[2]; }
	}

		if(m_AnimationTimer > 2000)	{ m_AnimationTimer = 0; }
	
		m_AnimationTimer += 5000*deltaTime;

		m_Sprite.setTexture(*m_Texture);
}

void IceBolt::Movement(float deltaTime)
{
    m_Sprite.move(m_Speed*deltaTime, 0);
}

bool IceBolt::IsAlive()
{
	return m_isAlive;
}

void IceBolt::KillObjekt()
{
	m_isAlive = false;
}

int IceBolt::GetPosition_x()const
{
	if(m_Speed > 0)
	{
		return m_Sprite.getPosition().x+20;
	}
	else if(m_Speed < 0)
	{
		return m_Sprite.getPosition().x-20;
	}
}

int IceBolt::GetPosition_y()const
{
	return m_Sprite.getPosition().y;
}

int IceBolt::GetTextureSize_x()const
{
	return TextureSize_x-16;
}

int IceBolt::GetTextureSize_y()const
{
	return TextureSize_y;
}

int IceBolt::GetDamage()const
{
	return DAMAGE;
}

Element IceBolt::GetElement()const
{
	return element;
}

Faction IceBolt::GetFaction()const
{
	return m_faction;
}

int IceBolt::GetSpeed()const
{
	return m_Speed;
}

int IceBolt::GetRange()
{
	return RANGE;
}

int IceBolt::GetElementPower()const
{
	return ELEMENTPOWER;
}