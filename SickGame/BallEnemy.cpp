#include "BallEnemy.h"
#include "GameFeatures.h"

#include "MemoryLeak.h"

static sf::Texture * T_StandingLeft	= NULL;
static sf::Texture * T_RunningLeft1	= NULL;
static sf::Texture * T_RunningLeft2	= NULL;
static sf::Texture * T_StandingRight= NULL;
static sf::Texture * T_RunningRight1= NULL;
static sf::Texture * T_RunningRight2= NULL;

static Element element = NEUTRAL;
static int  MOVEMENTSPEED = 300;

static int	TextureSize_x(37);
static int	TextureSize_y(42);

BallEnemy::BallEnemy(void)
{
}

BallEnemy::~BallEnemy(void)
{
}

void BallEnemy::LoadImage() 
{
	T_RunningLeft1 = new sf::Texture;
	T_StandingLeft = new sf::Texture;
	T_RunningLeft2 = new sf::Texture;

	T_RunningRight1 = new sf::Texture;
	T_StandingRight = new sf::Texture;
	T_RunningRight2 = new sf::Texture;

	if (!T_RunningLeft1->loadFromFile("Pictures/BallEnemy.png", sf::IntRect(TextureSize_x*0, TextureSize_y*1, TextureSize_x, TextureSize_y))){}
	if (!T_StandingLeft->loadFromFile("Pictures/BallEnemy.png", sf::IntRect(TextureSize_x*1, TextureSize_y*1, TextureSize_x, TextureSize_y))){}
	if (!T_RunningLeft2->loadFromFile("Pictures/BallEnemy.png", sf::IntRect(TextureSize_x*2, TextureSize_y*1, TextureSize_x, TextureSize_y))){}

	if (!T_RunningRight1->loadFromFile("Pictures/BallEnemy.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandingRight->loadFromFile("Pictures/BallEnemy.png", sf::IntRect(TextureSize_x*1, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_RunningRight2->loadFromFile("Pictures/BallEnemy.png", sf::IntRect(TextureSize_x*2, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
}

void BallEnemy::CloseImage()
{
	delete T_RunningLeft1;
	delete T_StandingLeft;
	delete T_RunningLeft2;

	delete T_RunningRight1;
	delete T_StandingRight;
	delete T_RunningRight2;
}

void BallEnemy::StandardSpell(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{
	GameFeatures::Create_MeleeAttack(Diraction_Right, Owners_Position_x, Owners_Position_y, TextureSize_x, TextureSize_y, faction);
	
}

void BallEnemy::SpecialAbility(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{
	
}

sf::Texture * BallEnemy::StandingLeft()const
{
	return T_StandingLeft;
}

sf::Texture * BallEnemy::RunningLeft1()const
{
	return T_RunningLeft1;
}

sf::Texture * BallEnemy::RunningLeft2()const
{
	return T_RunningLeft2;
}

sf::Texture * BallEnemy::StandingRight()const
{
	return T_StandingRight;
}

sf::Texture * BallEnemy::RunningRight1()const
{
	return T_RunningRight1;
}

sf::Texture * BallEnemy::RunningRight2()const
{
	return T_RunningRight2;
}

Element BallEnemy::GetElement()const
{
	return element;
}

int BallEnemy::GetTextureSize_x()const
{
	return TextureSize_x;
}

int BallEnemy::GetTextureSize_y()const
{
	return TextureSize_y;
}

int BallEnemy::GetStandardSpellRange()const
{
	return MeleeAttack::GetRange();
}

int BallEnemy::GetMovementSpeed()const
{
	return MOVEMENTSPEED;
}