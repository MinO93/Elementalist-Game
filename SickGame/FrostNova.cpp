#include "FrostNova.h"

#include "MemoryLeak.h"

static sf::Texture * T_FrostNova[2]	= {NULL, NULL};

static Element element = ICE;
static int DAMAGE = 0;
static int SPEED = 100;
static int RANGE = 0;
static int ELEMENTPOWER = 100;

static int	TextureSize_x(25);
static int	TextureSize_y(25);




FrostNova::FrostNova(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction, int NumberOfIceCubes) : 
	m_Speed(Diraction(Diraction_Right)),
	m_RangeLeft(RANGE),
	m_AnimationTimer(0),
	m_isAlive(true),
	m_Texture(T_FrostNova[0]),
	m_faction(faction),
	m_NumberOfIceCubes(NumberOfIceCubes),
	m_HasCreateFrostNova(false)
{
	m_Sprite.setTexture(*m_Texture);
	m_Sprite.setPosition(sf::Vector2f(Owners_Position_x, Owners_Position_y));
}

FrostNova::~FrostNova(void)
{
}

//Denna funktion är Static
void FrostNova::LoadImage()
{
	T_FrostNova[0] = new sf::Texture;
	T_FrostNova[1] = new sf::Texture;

	T_FrostNova[0]->loadFromFile("Pictures/FrostNova.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, TextureSize_x, TextureSize_y));
	T_FrostNova[1]->loadFromFile("Pictures/FrostNova.png", sf::IntRect(TextureSize_x*1, TextureSize_y*0, TextureSize_x, TextureSize_y));

}

//Denna funktion är Static
void FrostNova::CloseImage()
{
	delete T_FrostNova[0];
	delete T_FrostNova[1];
}

void FrostNova::Update(float deltaTime)
{
	m_RangeLeft += deltaTime;

	if(m_RangeLeft > 0.4)
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
	
	if(m_RangeLeft > 0.05 && m_HasCreateFrostNova == false && m_NumberOfIceCubes > 0 )
	{
		m_HasCreateFrostNova = true;
		if (m_Speed > 0)
		{
			GameFeatures::Create_FrostNova(true, m_Sprite.getPosition().x + 15, m_Sprite.getPosition().y, m_faction, m_NumberOfIceCubes-1);
		}

		if (m_Speed < 0)
		{
			GameFeatures::Create_FrostNova(false, m_Sprite.getPosition().x - 15, m_Sprite.getPosition().y, m_faction, m_NumberOfIceCubes-1);
		}
	}
}

int FrostNova::Diraction(bool DiractionRight)
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


void FrostNova::Animations(float deltaTime)
{



	if(m_Speed >= 0)
	{
		m_Texture = T_FrostNova[1];
	}
	else if(m_Speed <= 0)
	{
		m_Texture = T_FrostNova[0];
	}

		if(m_AnimationTimer > 2000)	{ m_AnimationTimer = 0; }
	
		m_AnimationTimer += 5000*deltaTime;

		m_Sprite.setTexture(*m_Texture);
}

void FrostNova::Movement(float deltaTime)
{
  
}

bool FrostNova::IsAlive()
{
	return m_isAlive;
}

void FrostNova::KillObjekt()
{
//	m_isAlive = false;
}

int FrostNova::GetPosition_x()const
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

int FrostNova::GetPosition_y()const
{
	return m_Sprite.getPosition().y;
}

int FrostNova::GetTextureSize_x()const
{
	return TextureSize_x-16;
}

int FrostNova::GetTextureSize_y()const
{
	return TextureSize_y;
}

int FrostNova::GetDamage()const
{
	return DAMAGE;
}

Element FrostNova::GetElement()const
{
	return element;
}

Faction FrostNova::GetFaction()const
{
	return m_faction;
}

int FrostNova::GetSpeed()const
{
	return m_Speed;
}

int FrostNova::GetRange()
{
	return RANGE;
}

int FrostNova::GetElementPower()const
{
	return ELEMENTPOWER;
}