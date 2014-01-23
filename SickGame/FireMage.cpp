#include "FireMage.h"
#include "GameFeatures.h"

#include "MemoryLeak.h"

static sf::Texture * T_StandingLeft	= NULL;
static sf::Texture * T_RunningLeft1	= NULL;
static sf::Texture * T_RunningLeft2	= NULL;
static sf::Texture * T_StandingRight= NULL;
static sf::Texture * T_RunningRight1= NULL;
static sf::Texture * T_RunningRight2= NULL;

static Element element = FIRE;
static int  MOVEMENTSPEED = 50;

static int	TextureSize_x(256/8);
static int	TextureSize_y(288/6);

FireMage::FireMage(void)
{
}

FireMage::~FireMage(void)
{
}

void FireMage::LoadImage() 
{
	T_RunningLeft1 = new sf::Texture;
	T_StandingLeft = new sf::Texture;
	T_RunningLeft2 = new sf::Texture;

	T_RunningRight1 = new sf::Texture;
	T_StandingRight = new sf::Texture;
	T_RunningRight2 = new sf::Texture;

	if (!T_RunningLeft1->loadFromFile("Pictures/RedMage.png", sf::IntRect(TextureSize_x*6, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandingLeft->loadFromFile("Pictures/RedMage.png", sf::IntRect(TextureSize_x*7, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_RunningLeft2->loadFromFile("Pictures/RedMage.png", sf::IntRect(TextureSize_x*0, TextureSize_y*1, TextureSize_x, TextureSize_y))){}

	if (!T_RunningRight1->loadFromFile("Pictures/RedMage-Mirrowed.png", sf::IntRect(TextureSize_x*1, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandingRight->loadFromFile("Pictures/RedMage-Mirrowed.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_RunningRight2->loadFromFile("Pictures/RedMage-Mirrowed.png", sf::IntRect(TextureSize_x*7, TextureSize_y*1, TextureSize_x, TextureSize_y))){}
}

void FireMage::CloseImage()
{
	delete T_RunningLeft1;
	delete T_StandingLeft;
	delete T_RunningLeft2;

	delete T_RunningRight1;
	delete T_StandingRight;
	delete T_RunningRight2;
}

void FireMage::StandardSpell(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{
	GameFeatures::Create_FireBolt(Diraction_Right, Owners_Position_x, Owners_Position_y+10, faction);
}

void FireMage::SpecialAbility(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{
	GameFeatures::Create_FireBolt(Diraction_Right, Owners_Position_x-20, Owners_Position_y+20, faction);
	GameFeatures::Create_FireBolt(Diraction_Right, Owners_Position_x, Owners_Position_y+10, faction);
	GameFeatures::Create_FireBolt(Diraction_Right, Owners_Position_x, Owners_Position_y+10, faction);
	GameFeatures::Create_FireBolt(Diraction_Right, Owners_Position_x-20, Owners_Position_y, faction);
	GameFeatures::Create_FireBolt(Diraction_Right, Owners_Position_x, Owners_Position_y, ENEMY);
}

sf::Texture * FireMage::StandingLeft()const
{
	return T_StandingLeft;
}

sf::Texture * FireMage::RunningLeft1()const
{
	return T_RunningLeft1;
}

sf::Texture * FireMage::RunningLeft2()const
{
	return T_RunningLeft2;
}

sf::Texture * FireMage::StandingRight()const
{
	return T_StandingRight;
}

sf::Texture * FireMage::RunningRight1()const
{
	return T_RunningRight1;
}

sf::Texture * FireMage::RunningRight2()const
{
	return T_RunningRight2;
}

Element FireMage::GetElement()const
{
	return element;
}

int FireMage::GetTextureSize_x()const
{
	return TextureSize_x;
}

int FireMage::GetTextureSize_y()const
{
	return TextureSize_y;
}

int FireMage::GetStandardSpellRange()const
{
	return FireBolt::GetRange();
}

int FireMage::GetMovementSpeed()const
{
	return MOVEMENTSPEED;
}