#include "StandardWind.h"

#include "MemoryLeak.h"

static sf::Texture * T_StandardWind[3]	= {NULL, NULL, NULL};

static Element element = WIND;
static int DAMAGE = 0;
static int SPEED = 500;
static int RANGE = 500;
static int ELEMENTPOWER = 100;

static int	TextureSize_x(34);
static int	TextureSize_y(45);


StandardWind::StandardWind(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) : 
	m_Damage(0),
	m_Speed(Diraction(Diraction_Right)),
	m_AnimationTimer(0),
	m_isAlive(true),
	m_Texture(T_StandardWind[0]),
	m_faction(faction),
	m_RangeLeft(RANGE)
{
	m_Sprite.setTexture(*m_Texture);
	m_Sprite.setPosition(sf::Vector2f(Owners_Position_x, Owners_Position_y));
}

StandardWind::~StandardWind(void)
{
}

//Denna funktion är Static
void StandardWind::LoadImage()
{
	T_StandardWind[0] = new sf::Texture;
	T_StandardWind[1] = new sf::Texture;
	T_StandardWind[2] = new sf::Texture;


	if (!T_StandardWind[0]->loadFromFile("Pictures/StandardWind.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandardWind[1]->loadFromFile("Pictures/StandardWind.png", sf::IntRect(TextureSize_x*1, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandardWind[2]->loadFromFile("Pictures/StandardWind.png", sf::IntRect(TextureSize_x*2, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
}

//Denna funktion är Static
void StandardWind::CloseImage()
{
	delete T_StandardWind[0];
	delete T_StandardWind[1];
	delete T_StandardWind[2];
}

void StandardWind::Update(float deltaTime)
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

int StandardWind::Diraction(bool DiractionRight)
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


void StandardWind::Animations(float deltaTime)
{


		if(		m_AnimationTimer < 200)	{ m_Texture = T_StandardWind[1]; }
		else if(m_AnimationTimer < 400)	{ m_Texture = T_StandardWind[0]; }
		else if(m_AnimationTimer < 600)	{ m_Texture = T_StandardWind[1]; }
		else if(m_AnimationTimer < 800)	{ m_Texture = T_StandardWind[2]; }

		if(m_AnimationTimer > 1000)	{ m_AnimationTimer = 0; }
	
		m_AnimationTimer += 5000*deltaTime;

		m_Sprite.setTexture(*m_Texture);
}

void StandardWind::Movement(float deltaTime)
{

	int x = m_Sprite.getPosition().x;
	int y = m_Sprite.getPosition().y;

    m_Sprite.move(m_Speed*deltaTime, 0);
}

bool StandardWind::IsAlive()
{
	return m_isAlive;
}

void StandardWind::KillObjekt()
{
	m_isAlive = false;
}

int StandardWind::GetPosition_x()const
{
	return m_Sprite.getPosition().x;
}

int StandardWind::GetPosition_y()const
{
	return m_Sprite.getPosition().y;
}

int StandardWind::GetTextureSize_x()const
{
	return TextureSize_x;
}

int StandardWind::GetTextureSize_y()const
{
	return TextureSize_y;
}

int StandardWind::GetDamage()const
{
	return DAMAGE;
}

Element StandardWind::GetElement()const
{
	return element;
}

Faction StandardWind::GetFaction()const
{
	return m_faction;
}

int StandardWind::GetSpeed()const
{
	return m_Speed;
}

int StandardWind::GetRange()
{
	return RANGE;
}

int StandardWind::GetElementPower()const
{
	return ELEMENTPOWER;
}