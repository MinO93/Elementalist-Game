#include "FrostMage.h"
#include "GameFeatures.h"

#include "MemoryLeak.h"

static sf::Texture * T_StandingLeft	= NULL;
static sf::Texture * T_RunningLeft1	= NULL;
static sf::Texture * T_RunningLeft2	= NULL;

static sf::Texture * T_StandingRight= NULL;
static sf::Texture * T_RunningRight1= NULL;
static sf::Texture * T_RunningRight2= NULL;

static Element element = WATER;
static int  MOVEMENTSPEED = 50;

static int	TextureSize_x(256/8);
static int	TextureSize_y(288/6);

FrostMage::FrostMage(void)
{
}

FrostMage::~FrostMage(void)
{
}

void FrostMage::LoadImage() 
{
	T_RunningLeft1 = new sf::Texture;
	T_StandingLeft = new sf::Texture;
	T_RunningLeft2 = new sf::Texture;

	T_RunningRight1 = new sf::Texture;
	T_StandingRight = new sf::Texture;
	T_RunningRight2 = new sf::Texture;

	if (!T_RunningLeft1->loadFromFile("Pictures/BlueMage.png", sf::IntRect(TextureSize_x*6, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandingLeft->loadFromFile("Pictures/BlueMage.png", sf::IntRect(TextureSize_x*7, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_RunningLeft2->loadFromFile("Pictures/BlueMage.png", sf::IntRect(TextureSize_x*0, TextureSize_y*1, TextureSize_x, TextureSize_y))){}

	if (!T_RunningRight1->loadFromFile("Pictures/BlueMage-Mirrowed.png", sf::IntRect(TextureSize_x*1, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_StandingRight->loadFromFile("Pictures/BlueMage-Mirrowed.png", sf::IntRect(TextureSize_x*0, TextureSize_y*0, TextureSize_x, TextureSize_y))){}
	if (!T_RunningRight2->loadFromFile("Pictures/BlueMage-Mirrowed.png", sf::IntRect(TextureSize_x*7, TextureSize_y*1, TextureSize_x, TextureSize_y))){}
}

void FrostMage::CloseImage()
{
	delete T_RunningLeft1;
	delete T_StandingLeft;
	delete T_RunningLeft2;

	delete T_RunningRight1;
	delete T_StandingRight;
	delete T_RunningRight2;
}

void FrostMage::StandardSpell(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{
	GameFeatures::Create_IceBolt(Diraction_Right, Owners_Position_x, Owners_Position_y + 10, faction);
}

void FrostMage::SpecialAbility(bool Diraction_Right, float Owners_Position_x, float Owners_Position_y, Faction faction) 
{
	GameFeatures::Create_FrostNova(true, Owners_Position_x, Owners_Position_y + TextureSize_y -25 , faction, 5);
	GameFeatures::Create_FrostNova(false, Owners_Position_x, Owners_Position_y + TextureSize_y -25 , faction, 5);
}

sf::Texture * FrostMage::StandingLeft()const
{
	return T_StandingLeft;
}

sf::Texture * FrostMage::RunningLeft1()const
{
	return T_RunningLeft1;
}

sf::Texture * FrostMage::RunningLeft2()const
{
	return T_RunningLeft2;
}

sf::Texture * FrostMage::StandingRight()const
{
	return T_StandingRight;
}

sf::Texture * FrostMage::RunningRight1()const
{
	return T_RunningRight1;
}

sf::Texture * FrostMage::RunningRight2()const
{
	return T_RunningRight2;
}

Element FrostMage::GetElement()const
{
	return element;
}

int FrostMage::GetTextureSize_x()const
{
	return TextureSize_x;
}

int FrostMage::GetTextureSize_y()const
{
	return TextureSize_y;
}

int FrostMage::GetStandardSpellRange()const
{
	return IceBolt::GetRange();
}

int FrostMage::GetMovementSpeed()const
{
	return MOVEMENTSPEED;
}