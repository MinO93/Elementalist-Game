#include "AirMage.h"
#include "GameFeatures.h"

#include "MemoryLeak.h"

static sf::Texture * T_StandingLeft	= NULL;
static sf::Texture * T_RunningLeft1	= NULL;
static sf::Texture * T_RunningLeft2	= NULL;
static sf::Texture * T_StandingRight= NULL;
static sf::Texture * T_RunningRight1= NULL;
static sf::Texture * T_RunningRight2= NULL;

static Element element = WIND;
static int  MOVEMENTSPEED = 50;

static int	TextureSize_x(256/8);
static int	TextureSize_y(288/6);

AirMage::AirMage(void)
{
}

AirMage::~AirMage(void)
{
}

void AirMage::LoadImage() 
{
	T_RunningLeft1 = new sf::Texture;
	T_StandingLeft = new sf::Texture;
	T_RunningLeft2 = new sf::Texture;

	T_RunningRight1 = new sf::Texture;
	T_StandingRight = new sf::Texture;
	T_RunningRight2 = new sf::Texture;

	if (!T_RunningLeft1->loadFromFile("Pictures/WhiteMage.png", sf::IntRect(TextureSize_x*6, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandingLeft->loadFromFile("Pictures/WhiteMage.png", sf::IntRect(TextureSize_x*7, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_RunningLeft2->loadFromFile("Pictures/WhiteMage.png", sf::IntRect(TextureSize_x*0, TextureSize_y*1, TextureSize_x, TextureSize_y))){}

	if (!T_RunningRight1->loadFromFile("Pictures/WhiteMage-Mirrowed.png", sf::IntRect(TextureSize_x*1, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandingRight->loadFromFile("Pictures/WhiteMage-Mirrowed.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_RunningRight2->loadFromFile("Pictures/WhiteMage-Mirrowed.png", sf::IntRect(TextureSize_x*7, TextureSize_y*1, TextureSize_x, TextureSize_y))){}
}

void AirMage::CloseImage()
{
	delete T_RunningLeft1;
	delete T_StandingLeft;
	delete T_RunningLeft2;

	delete T_RunningRight1;
	delete T_StandingRight;
	delete T_RunningRight2;
}

void AirMage::StandardSpell(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{
	GameFeatures::Create_StandardWind(Diraction_Right, Owners_Position_x, Owners_Position_y, faction);
}

void AirMage::SpecialAbility(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{

	Faction ChangeFaction;

	if(faction == ENEMY)
	{
		ChangeFaction = FRIEND;
	}
	else if(faction == FRIEND)
	{
		ChangeFaction = ENEMY;
	}

	GameFeatures::Create_StandardWind(Diraction_Right, Owners_Position_x, Owners_Position_y, ChangeFaction);

}

sf::Texture * AirMage::StandingLeft()const
{
	return T_StandingLeft;
}

sf::Texture * AirMage::RunningLeft1()const
{
	return T_RunningLeft1;
}

sf::Texture * AirMage::RunningLeft2()const
{
	return T_RunningLeft2;
}

sf::Texture * AirMage::StandingRight()const
{
	return T_StandingRight;
}

sf::Texture * AirMage::RunningRight1()const
{
	return T_RunningRight1;
}

sf::Texture * AirMage::RunningRight2()const
{
	return T_RunningRight2;
}

Element AirMage::GetElement()const
{
	return element;
}

int AirMage::GetTextureSize_x()const
{
	return TextureSize_x;
}

int AirMage::GetTextureSize_y()const
{
	return TextureSize_y;
}

int AirMage::GetStandardSpellRange()const
{
	return StandardWind::GetRange();
}

int AirMage::GetMovementSpeed()const
{
	return MOVEMENTSPEED;
}