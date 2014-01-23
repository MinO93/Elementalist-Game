#include "MeleeAttack.h"

#include "MemoryLeak.h"

static sf::Texture * T_MeleeAttack[3]	= {NULL, NULL, NULL};

static Element element = MELEE;
static int DAMAGE = 100;
static int SPEED = 1;
static int RANGE = 2;
static int ELEMENTPOWER = 100;

static int	TextureSize_x(0);
static int	TextureSize_y(0);



MeleeAttack::MeleeAttack(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, int Owners_TextureSize_x, int Owners_TextureSize_y, Faction faction) : 
	m_Damage(0),
	m_Speed(Diraction(Diraction_Right)),
	m_AnimationTimer(0),
	m_isAlive(true),
	m_Texture(T_MeleeAttack[0]),
	m_faction(faction),
	m_RangeLeft(1),
	m_Size_x(Owners_TextureSize_x+10),
	m_Size_y(Owners_TextureSize_y)

{
	m_Sprite.setTexture(*m_Texture);
	m_Sprite.setPosition(sf::Vector2f(Owners_Position_x-5, Owners_Position_y));
}

MeleeAttack::~MeleeAttack(void)
{
}

//Denna funktion är Static
void MeleeAttack::LoadImage()
{
	T_MeleeAttack[0] = new sf::Texture;
	T_MeleeAttack[1] = new sf::Texture;
	T_MeleeAttack[2] = new sf::Texture;


	if (!T_MeleeAttack[0]->loadFromFile("Pictures/StandardWind.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, 0, 0))){}
	if (!T_MeleeAttack[1]->loadFromFile("Pictures/StandardWind.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, 0, 0))){}
	if (!T_MeleeAttack[2]->loadFromFile("Pictures/StandardWind.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, 0, 0))){}
}

//Denna funktion är Static
void MeleeAttack::CloseImage()
{
	delete T_MeleeAttack[0];
	delete T_MeleeAttack[1];
	delete T_MeleeAttack[2];
}

void MeleeAttack::Update(float deltaTime)
{
	m_RangeLeft -= SPEED * deltaTime ;
	if(m_RangeLeft < 0)
	{
		m_isAlive = false;
	}

	GameFeatures::DamageDealerFunction(this);


//	Movement(deltaTime);
//	Animations(deltaTime);
}

int MeleeAttack::Diraction(bool DiractionRight)
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


void MeleeAttack::Animations(float deltaTime)
{
		if(		m_AnimationTimer < 200)	{ m_Texture = T_MeleeAttack[1]; }
		else if(m_AnimationTimer < 400)	{ m_Texture = T_MeleeAttack[0]; }
		else if(m_AnimationTimer < 600)	{ m_Texture = T_MeleeAttack[1]; }
		else if(m_AnimationTimer < 800)	{ m_Texture = T_MeleeAttack[2]; }

		if(m_AnimationTimer > 1000)	{ m_AnimationTimer = 0; }
	
		m_AnimationTimer += 5000*deltaTime;

		m_Sprite.setTexture(*m_Texture);
}

void MeleeAttack::Movement(float deltaTime)
{

    m_Sprite.move(m_Speed*deltaTime, 0);
}

bool MeleeAttack::IsAlive()
{
	return m_isAlive;
}

void MeleeAttack::KillObjekt()
{
	m_isAlive = false;
}

int MeleeAttack::GetPosition_x()const
{
	return m_Sprite.getPosition().x;
}

int MeleeAttack::GetPosition_y()const
{
	return m_Sprite.getPosition().y;
}

int MeleeAttack::GetTextureSize_x()const
{
	return m_Size_x;
}

int MeleeAttack::GetTextureSize_y()const
{
	return m_Size_y;
}

int MeleeAttack::GetDamage()const
{
	return DAMAGE;
}

Element MeleeAttack::GetElement()const
{
	return element;
}

Faction MeleeAttack::GetFaction()const
{
	return m_faction;
}

int MeleeAttack::GetSpeed()const
{
	return m_Speed;
}

int MeleeAttack::GetRange()
{
	return RANGE;
}

int MeleeAttack::GetElementPower()const
{
	return ELEMENTPOWER;
}