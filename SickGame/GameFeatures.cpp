#include "GameFeatures.h"
#include "Level.h"
#include "StandardWind.h"
#include "MeleeAttack.h"
#include "IceBolt.h"
#include "FrostNova.h"
#include "FireBolt.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

#include "MemoryLeak.h"

const static int GameBlockSize = 55;
const static int AreaCheck = 1;
	
static std::string * levelPaths;
static Level * m_Levels;

typedef std::vector <AbilityObjekt*> AbilityObjektVector;	
static AbilityObjektVector m_AbilityObjektVector;

typedef std::vector <Enemy*> EnemyVector;
EnemyVector m_EnemyVector;

typedef std::vector <Player*> PlayerVector;
PlayerVector m_PlayerVector;

Player *player;

static int m_Map_Level;
static bool m_Goal;
static int LEVEL_COUNT;
static TileMap * map;
static int m_Goal_Position_x;
static int m_Goal_Position_y;

GameFeatures::GameFeatures(void)
{
}


GameFeatures::~GameFeatures(void)
{
}

void GameFeatures::LoadImages()
{
	FrostMage::LoadImage();
	AirMage::LoadImage();
	FireMage::LoadImage();
	FireBolt::LoadImage();
	IceBolt::LoadImage();
	StandardWind::LoadImage();
	BallEnemy::LoadImage();
	MeleeAttack::LoadImage();
	FrostNova::LoadImage();

	Player::LoadSound();
}

void GameFeatures::CloseImages()
{
	FrostMage::CloseImage();
	AirMage::CloseImage();
	FireMage::CloseImage();
	FireBolt::CloseImage();
	IceBolt::CloseImage();
	StandardWind::CloseImage();
	BallEnemy::CloseImage();
	MeleeAttack::CloseImage();
	FrostNova::CloseImage();
}

void GameFeatures::Update(float deltaTime)
{
	
	// Uppdaterar alla spells
	AbilityObjektVector temp(m_AbilityObjektVector);
	for(AbilityObjektVector::iterator i = temp.begin(); i != temp.end(); i++)
	{
		(*i)->Update(deltaTime);
	}

	// Uppdaterar alla fiender
	for(EnemyVector::iterator i = m_EnemyVector.begin(); i != m_EnemyVector.end(); i++)
	{
		(*i)->Update(deltaTime, player->GetPosition_x(), player->GetPosition_y());
	}

	// Uppdaterar spelaren
	player->Update(deltaTime);

	// Börjar om spelaren dör eller hamnar utanför banan
	if (player->GetPosition_y() > m_Levels[m_Map_Level].GetMapSize_y()*GameBlockSize + 200 
	||	player->GetPosition_y() < -200 
	|| sf::Keyboard::isKeyPressed(sf::Keyboard::R)
	|| !player->IsAlive()
	)
	{
		Initialize();
	} 

	if (Collision(player->GetPosition_x()+25, player->GetPosition_y()+25, 1, 1, m_Goal_Position_x, m_Goal_Position_y, GameBlockSize, GameBlockSize))
	{
		m_Goal = true;
	}

	KillObjekt();
}

void GameFeatures::Initialize()
{
	EraseAllObjekts();
	SpawnEntities();
	player->initilize();
}

void GameFeatures::DeleteObjektsBeforeExitGame()
{

	for(int i = 0; LEVEL_COUNT > i; i++)
	{
		m_Levels[i].DeleteMapData();
	}

	delete map;
	delete player;
	delete m_Levels;
	delete []levelPaths;
}

sf::Vector2f GameFeatures::CameraUpdate(int GameWindowSize_x, int GameWindowSize_y)
{
	// om spelaren kommer i kanten är kameran fortfarande vara inne i banan

	// Sätter kameran på spelaren - X-led
	int View_x = player->GetPosition_x();

	if(player->GetPosition_x() < GameWindowSize_x/2)
	{
		View_x = GameWindowSize_x/2;
	}
	// om spelaren kommer i kanten är kameran fortfarande inne i banan
	if(player->GetPosition_x() > m_Levels[m_Map_Level].GetMapSize_x()*GameBlockSize - GameWindowSize_x/2)
	{
		View_x = m_Levels[m_Map_Level].GetMapSize_x()*GameBlockSize - GameWindowSize_x/2;
	}
	//// Sätter kameran på spelaren - Y-led
	int View_y = player->GetPosition_y();

	// om spelaren kommer i kanten är kameran fortfarande inne i banan
	if(player->GetPosition_y() < GameWindowSize_y/2)
	{
		View_y = GameWindowSize_y/2;
	}
	else if(player->GetPosition_y() > m_Levels[m_Map_Level].GetMapSize_y()*GameBlockSize - GameWindowSize_y/2)
	{
		View_y = m_Levels[m_Map_Level].GetMapSize_y()*GameBlockSize - GameWindowSize_y/2;
	}

	return sf::Vector2f(View_x, View_y);
}

void GameFeatures::Display(sf::RenderWindow *window)
{
	// Ritar bakgrunden/Banan
	window->draw(*map);

	// Ritar alla Spells
	for(AbilityObjektVector::iterator i = m_AbilityObjektVector.begin(); i != m_AbilityObjektVector.end(); i++)
	{
		window->draw(*(*i));
	}

	// Ritar ut spelaren
	window->draw(*player);

	// Ritar ut alla fiender
	for(EnemyVector::iterator i = m_EnemyVector.begin(); i != m_EnemyVector.end(); i++)
	{
		window->draw(*(*i));
	}
}



bool GameFeatures::Check_Collision_With_StandardBlocks(Creature &creature)
{
	int GameObjekts_Position_x	= creature.GetPosition_x();
	int GameObjekts_Position_y	= creature.GetPosition_y();
	int GameObjekts_Size_x		= creature.GetTextureSize_x();
	int GameObjekts_Size_y		= creature.GetTextureSize_y();

	int AreaCheckArray[1 + AreaCheck *2];
	
	int Player_x = (GameObjekts_Position_x + GameObjekts_Size_x/2)/GameBlockSize;
	int Player_y = (GameObjekts_Position_y + GameObjekts_Size_y/2)/GameBlockSize;

	int Player_current_Position = Player_y * m_Levels[m_Map_Level].GetMapSize_x() + Player_x;

	int AreaCheckCounter = AreaCheck * -1;

		for(int i = 0; i < 1 + AreaCheck*2; i++)
			{
				AreaCheckArray[i] = Player_current_Position + m_Levels[m_Map_Level].GetMapSize_x()*AreaCheckCounter - AreaCheck;
				AreaCheckCounter++;
			}

	for(int it = 0; it < 1 + AreaCheck *2 ; it++ )
	{
		for(int i = AreaCheckArray[it]; i < 1 + AreaCheck *2 + AreaCheckArray[it]; i++ )
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x();
			int y = i / m_Levels[m_Map_Level].GetMapSize_x();

			if( i > m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y() || i < 0)
			{
				continue;
			}

			if( 
					m_Levels[m_Map_Level].GetMapData()[i] == 2 ||
					m_Levels[m_Map_Level].GetMapData()[i] == 3 ||
					m_Levels[m_Map_Level].GetMapData()[i] == 1
				)
			{
				if(Collision(GameObjekts_Position_x, GameObjekts_Position_y, GameObjekts_Size_x, GameObjekts_Size_y, x * GameBlockSize, y * GameBlockSize, GameBlockSize, GameBlockSize))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool GameFeatures::Check_Collision_With_StandardBlocks(AbilityObjekt *abilityobjekt)
{
	int GameObjekts_Position_x	= abilityobjekt->GetPosition_x();
	int GameObjekts_Position_y	= abilityobjekt->GetPosition_y();
	int GameObjekts_Size_x		= abilityobjekt->GetTextureSize_x();
	int GameObjekts_Size_y		= abilityobjekt->GetTextureSize_y();

	int AreaCheckArray[1 + AreaCheck *2];
	
	int Player_x = (GameObjekts_Position_x + GameObjekts_Size_x/2)/GameBlockSize;
	int Player_y = (GameObjekts_Position_y + GameObjekts_Size_y/2)/GameBlockSize;

	int Player_current_Position = Player_y * m_Levels[m_Map_Level].GetMapSize_x() + Player_x;

	int AreaCheckCounter = AreaCheck * -1;

		for(int i = 0; i < 1 + AreaCheck*2; i++)
			{
				AreaCheckArray[i] = Player_current_Position + m_Levels[m_Map_Level].GetMapSize_x()*AreaCheckCounter - AreaCheck;
				AreaCheckCounter++;
			}

	for(int it = 0; it < 1 + AreaCheck *2 ; it++ )
	{
		for(int i = AreaCheckArray[it]; i < 1 + AreaCheck *2 + AreaCheckArray[it]; i++ )
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x();
			int y = i / m_Levels[m_Map_Level].GetMapSize_x();

			if( i > m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y() || i < 0)
			{
				continue;
			}

			if( 
					m_Levels[m_Map_Level].GetMapData()[i] == 2 ||
					m_Levels[m_Map_Level].GetMapData()[i] == 3 ||
					m_Levels[m_Map_Level].GetMapData()[i] == 1
				)
			{
				if(Collision(GameObjekts_Position_x, GameObjekts_Position_y, GameObjekts_Size_x, GameObjekts_Size_y, x * GameBlockSize, y * GameBlockSize, GameBlockSize, GameBlockSize))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool GameFeatures::Collision(
float GameObjekt_Position_x, float GameObjekt_Position_y, 
float GameObjekt_Size_x,	 float GameObjekt_Size_y, 

float GameBlock_Position_x,  float GameBlock_Position_y,
float GameBlock_Size_x,		 float GameBlock_Size_y )
{
	if(
	GameObjekt_Position_x + GameObjekt_Size_x >=  GameBlock_Position_x && GameObjekt_Position_x <= GameBlock_Position_x + GameBlock_Size_x
	&&
	GameObjekt_Position_y + GameObjekt_Size_y >= GameBlock_Position_y && GameObjekt_Position_y <= GameBlock_Position_y + GameBlock_Size_y
	)
	{
		return true;
	}
		return false;
}


void GameFeatures::KillObjekt()
{
	for(AbilityObjektVector::iterator i = m_AbilityObjektVector.begin(); i != m_AbilityObjektVector.end(); )
	{
		if((*i)->IsAlive() == false)
		{
			delete (*i);
			i = m_AbilityObjektVector.erase(i);
		}
		else
		{
			i++;
		}
	}

	for(EnemyVector::iterator i = m_EnemyVector.begin(); i != m_EnemyVector.end(); )
	{
		if((*i)->IsAlive() == false)
		{
			delete (*i);
			i = m_EnemyVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void GameFeatures::EraseAllObjekts()
{
	for(AbilityObjektVector::iterator i = m_AbilityObjektVector.begin(); i != m_AbilityObjektVector.end();)
	{
			delete (*i);
			i = m_AbilityObjektVector.erase(i);
	}

	for(EnemyVector::iterator i = m_EnemyVector.begin(); i != m_EnemyVector.end();)
	{
			delete (*i);
			i = m_EnemyVector.erase(i);
	}

}


void GameFeatures::Create_Player(int spelare)
{
	if(spelare == 0)
	{
		player = new Player(spelare);
	}
}

void GameFeatures::Set_PlayerPosition(int x, int y)
{
	player->SetPosition(x, y);
}

void GameFeatures::Create_Enemy(int x, int y, int creature_select)
{
	m_EnemyVector.push_back(new Enemy(x, y, ENEMY, creature_select));
}


void GameFeatures::Create_StandardWind(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction)
{
	m_AbilityObjektVector.push_back(new StandardWind(Diraction_Right, Owners_Position_x, Owners_Position_y, faction));
}

void GameFeatures::Create_FireBolt(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction)
{
	m_AbilityObjektVector.push_back(new FireBolt(Diraction_Right, Owners_Position_x, Owners_Position_y, faction));
}

void GameFeatures::Create_IceBolt(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction)
{
	m_AbilityObjektVector.push_back(new IceBolt(Diraction_Right, Owners_Position_x, Owners_Position_y, faction));
}

void GameFeatures::Create_MeleeAttack(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, int TextureSize_x, int TextureSize_y, Faction faction)
{
	m_AbilityObjektVector.push_back(new MeleeAttack(Diraction_Right, Owners_Position_x, Owners_Position_y, TextureSize_x, TextureSize_y, faction));
}

void GameFeatures::Create_FrostNova(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction, int NumberOfIceCubes)
{
	m_AbilityObjektVector.push_back(new FrostNova(Diraction_Right, Owners_Position_x, Owners_Position_y, faction, NumberOfIceCubes));
}

void GameFeatures::DamageDealerFunction(AbilityObjekt *abilityobjekt)
{
	AbilityObjekt * i_abilityObjekt = abilityobjekt;

	Element SpellElement	= i_abilityObjekt->GetElement();
	Faction SpellFaction	= i_abilityObjekt->GetFaction();
	int	SpellTextureSize_x	= i_abilityObjekt->GetTextureSize_x();
	int	SpellTextureSize_y	= i_abilityObjekt->GetTextureSize_y();
		
	if(SpellFaction == FRIEND)
	{
		for(EnemyVector::iterator i_Creature = m_EnemyVector.begin(); i_Creature != m_EnemyVector.end(); i_Creature++ )
		{
			Element CreatureElement		= (*i_Creature)->GetElement();
			int CreatureTextureSize_x	= (*i_Creature)->GetTextureSize_x();
			int CreatureTextureSize_y	= (*i_Creature)->GetTextureSize_y();
			if(Collision( 
				(*i_Creature)->GetPosition_x(), (*i_Creature)->GetPosition_y(), (*i_Creature)->GetTextureSize_x(), (*i_Creature)->GetTextureSize_y(),
				i_abilityObjekt->GetPosition_x(), i_abilityObjekt->GetPosition_y(), i_abilityObjekt->GetTextureSize_x(), i_abilityObjekt->GetTextureSize_y()
				))
			{
				i_abilityObjekt->KillObjekt();
				(*i_Creature)->ReceiveDamage(i_abilityObjekt->GetDamage());

				if(SpellElement == WIND)
				{
					(*i_Creature)->GetHitByWind(i_abilityObjekt->GetSpeed());
				}

				if(SpellElement == ICE)
				{
					(*i_Creature)->GetHitByIce(i_abilityObjekt->GetElementPower());
				}

			}
		}
	}
	if(SpellFaction == ENEMY)
	{
		if(Collision( 
			player->GetPosition_x(), player->GetPosition_y(), player->GetTextureSize_x(), player->GetTextureSize_y(),
			i_abilityObjekt->GetPosition_x(), i_abilityObjekt->GetPosition_y(), i_abilityObjekt->GetTextureSize_x(), i_abilityObjekt->GetTextureSize_y()
			))
		{
		i_abilityObjekt->KillObjekt();
		player->ReceiveDamage(i_abilityObjekt->GetDamage());

				if(SpellElement == WIND)
			{
				player->GetHitByWind(i_abilityObjekt->GetSpeed());
			}
				if(SpellElement == ICE)
			{
				player->GetHitByIce(i_abilityObjekt->GetElementPower());
			}

		}
	}
}

void GameFeatures::SpawnEntities()
{
	int i = 0;

	// Sätter spelaren till Start position - Beroende vilken Map det är
	while(i < m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y())
	{
		if(	m_Levels[m_Map_Level].GetMapData()[i] == 5 ||
			m_Levels[m_Map_Level].GetMapData()[i] == 7 ||
			m_Levels[m_Map_Level].GetMapData()[i] == 11
			)
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x();
			int y = i /	m_Levels[m_Map_Level].GetMapSize_x();
			GameFeatures::Set_PlayerPosition((x * GameBlockSize) + GameBlockSize/2 - player->GetTextureSize_x()/2, y * GameBlockSize + 1);
			break;
		}
		i++;
	}

	i = 0;

	// Sätter fiendern till Start position - Beroende vilken Map det är
	while(i < m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y())
	{
		if(		m_Levels[m_Map_Level].GetMapData()[i] == 50
			||	m_Levels[m_Map_Level].GetMapData()[i] == 60
			||	m_Levels[m_Map_Level].GetMapData()[i] == 70
			)
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x();
			int y = i /	m_Levels[m_Map_Level].GetMapSize_x();
			GameFeatures::Create_Enemy(x*GameBlockSize, y*GameBlockSize, 0);
		}
		i++;
	}

	i = 0;

	while(i < m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y())
	{
		if(		m_Levels[m_Map_Level].GetMapData()[i] == 51
			|| m_Levels[m_Map_Level].GetMapData()[i] == 61
			|| m_Levels[m_Map_Level].GetMapData()[i] == 71
			)
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x();
			int y = i /	m_Levels[m_Map_Level].GetMapSize_x();
			GameFeatures::Create_Enemy(x*GameBlockSize, y*GameBlockSize, 1);
		}
		i++;
	}

	i = 0;

	while(i <m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y())
	{
		if(		m_Levels[m_Map_Level].GetMapData()[i] == 52
			||	m_Levels[m_Map_Level].GetMapData()[i] == 62
			||	m_Levels[m_Map_Level].GetMapData()[i] == 72
			)
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x();
			int y = i /	m_Levels[m_Map_Level].GetMapSize_x();
			GameFeatures::Create_Enemy(x*GameBlockSize, y*GameBlockSize, 2);
		}
		i++;
	}

	i = 0;

		while(i < m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y())
	{
		if(	   m_Levels[m_Map_Level].GetMapData()[i] == 53
			|| m_Levels[m_Map_Level].GetMapData()[i] == 63
			|| m_Levels[m_Map_Level].GetMapData()[i] == 73
			)
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x();
			int y = i / m_Levels[m_Map_Level].GetMapSize_x();
			GameFeatures::Create_Enemy(x*GameBlockSize, y*GameBlockSize, 3);
		}
		i++;
	}

	i = 0;

	while(i < m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y())
	{
		if(	m_Levels[m_Map_Level].GetMapData()[i] == 6 ||
			m_Levels[m_Map_Level].GetMapData()[i] == 8 ||
			m_Levels[m_Map_Level].GetMapData()[i] == 12 
			)
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x() ;
			int y = i / m_Levels[m_Map_Level].GetMapSize_x() ;

			m_Goal_Position_x = x * GameBlockSize;
			m_Goal_Position_y = y * GameBlockSize;
			break;
		}
		i++;
	}
}



//Laddar map ifrån
void GameFeatures::LoadMap()
{


	std::string scrap;
	LEVEL_COUNT = 0;

	std::ifstream MapPaths;
	MapPaths.open("Maps/MapPaths.txt");
	while (!MapPaths.eof())
	{
		LEVEL_COUNT++;
		MapPaths >> scrap;
	}

	MapPaths.close();

	MapPaths.open("Maps/MapPaths.txt");
	levelPaths = new std::string[ LEVEL_COUNT ];
	m_Levels = new Level[LEVEL_COUNT];

	for( int i = 0; i < LEVEL_COUNT; i++)
	{
		MapPaths >> levelPaths[i];

	}

	MapPaths.close();
	
	for( int i = 0; i < LEVEL_COUNT; i++) 
	{
		m_Levels[ i ].LoadLevel( levelPaths[ i ] );
	}

	
	std::cout << "All the " << LEVEL_COUNT << " was loaded." << std::endl;
}

void GameFeatures::InitializeNextLevel()
{
	// Ändrar indixet till Level Arrayen för att byta bana
	m_Map_Level++;
	if(m_Map_Level >= LEVEL_COUNT )
	{
		m_Map_Level = 0;
	}
	m_Goal = false;
		

	GameFeatures::Initialize();	// Spawnar om alla fiender samt Sätter spelaren på SpawnPlatsen
	SetGoalPosition();									// Sätter FinalPosition
	LoadTileMap();										// Laddar in hur banan ska ritas ut

}

void GameFeatures::SetGoalPosition()
{
	int i = 0;

	while(i < m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y())
	{
		if(	m_Levels[m_Map_Level].GetMapData()[i] == 6 ||
			m_Levels[m_Map_Level].GetMapData()[i] == 8 ||
			m_Levels[m_Map_Level].GetMapData()[i] == 12 
			)
		{
			int x = i % m_Levels[m_Map_Level].GetMapSize_x() ;
			int y = i / m_Levels[m_Map_Level].GetMapSize_x() ;

			m_Goal_Position_x = x * GameBlockSize;
			m_Goal_Position_y = y * GameBlockSize;
			break;
		}
		i++;
	}
}

void GameFeatures::LoadTileMap()
{
	int * MapDataWithOutEnemyID = new int[ m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y() ];

	// Ändrar Fiendens ID i TextMappen till ett o-kolliderat block, istället att det blir ett svart håll i banan
	for(int i = 0; i < m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y(); i++)
	{
		// Ändrar Fiendens ID till Luft
		if( m_Levels[m_Map_Level].GetMapData()[i] == 50
		||	m_Levels[m_Map_Level].GetMapData()[i] == 51
		||	m_Levels[m_Map_Level].GetMapData()[i] == 52
		||	m_Levels[m_Map_Level].GetMapData()[i] == 53
		||	m_Levels[m_Map_Level].GetMapData()[i] == 54
		||	m_Levels[m_Map_Level].GetMapData()[i] == 55
		||	m_Levels[m_Map_Level].GetMapData()[i] == 56
		||	m_Levels[m_Map_Level].GetMapData()[i] == 57
		||	m_Levels[m_Map_Level].GetMapData()[i] == 58
		||	m_Levels[m_Map_Level].GetMapData()[i] == 59
			)
		{
			MapDataWithOutEnemyID[i] = 0;
		}
		// Ändrar Fiendens ID till Sten
		else if (
			m_Levels[m_Map_Level].GetMapData()[i] == 60
		||	m_Levels[m_Map_Level].GetMapData()[i] == 61
		||	m_Levels[m_Map_Level].GetMapData()[i] == 62
		||	m_Levels[m_Map_Level].GetMapData()[i] == 63
		||	m_Levels[m_Map_Level].GetMapData()[i] == 64
		||	m_Levels[m_Map_Level].GetMapData()[i] == 65
		||	m_Levels[m_Map_Level].GetMapData()[i] == 66
		||	m_Levels[m_Map_Level].GetMapData()[i] == 67
		||	m_Levels[m_Map_Level].GetMapData()[i] == 68
		||	m_Levels[m_Map_Level].GetMapData()[i] == 69
			)
		{
			MapDataWithOutEnemyID[i] = 4;
		}
		// Ändrar Fiendens ID till Jord
		else if (
			m_Levels[m_Map_Level].GetMapData()[i] == 70
		||	m_Levels[m_Map_Level].GetMapData()[i] == 71
		||	m_Levels[m_Map_Level].GetMapData()[i] == 72
		||	m_Levels[m_Map_Level].GetMapData()[i] == 73
		||	m_Levels[m_Map_Level].GetMapData()[i] == 74
		||	m_Levels[m_Map_Level].GetMapData()[i] == 75
		||	m_Levels[m_Map_Level].GetMapData()[i] == 76
		||	m_Levels[m_Map_Level].GetMapData()[i] == 77
		||	m_Levels[m_Map_Level].GetMapData()[i] == 78
		||	m_Levels[m_Map_Level].GetMapData()[i] == 79
			)
		{
			MapDataWithOutEnemyID[i] = 10;
		}
		// Ändrar ingen skillnad om det inte är något fiende ID
		else
		{
		MapDataWithOutEnemyID[i] = m_Levels[m_Map_Level].GetMapData()[i];
		}
	}

	map->load("Pictures/tidesheet1.1.png", sf::Vector2u(GameBlockSize, GameBlockSize), MapDataWithOutEnemyID, m_Levels[m_Map_Level].GetMapSize_x(), m_Levels[m_Map_Level].GetMapSize_y());
	delete MapDataWithOutEnemyID;
}


bool GameFeatures::TurnEnemyDiraction(Creature &creature, bool Diraction_Right)
{
	// Om han går åt höger ska han kolla åt höger om det är ett icke stå bart block under sin pixel längs åt höger
	if(Diraction_Right == true)
	{
		// Letar vilket block han står på med sin pixel längst åt höger
		int x = ( creature.GetPosition_x() + creature.GetTextureSize_x() - 1    ) / GameBlockSize;
		int y = ( creature.GetPosition_y() + creature.GetTextureSize_y()/2      ) / GameBlockSize;
		y += 1;		//flyttar ett steg neråt för att få veta vilket sorts block det är under pixeln
		
		// Letar fram block ID
		int i = y * m_Levels[m_Map_Level].GetMapSize_x() + x;

		// om indixet blir minder 0 eller större än mappen, blir det då 0.
		// Leder till en bugg annars
		if( i > m_Levels[m_Map_Level].GetMapSize_x() *m_Levels[m_Map_Level].GetMapSize_y() ||
			i < 0)
		{
			i = 0;
		}
		//Om blocket är icke stå bart block så ska han byta riktning
		if(	m_Levels[m_Map_Level].GetMapData()[i] != 1 &&
			m_Levels[m_Map_Level].GetMapData()[i] != 2 &&
			m_Levels[m_Map_Level].GetMapData()[i] != 3
			)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	// Om han går åt höger ska han kolla åt vänster om det är ett icke stå bart block under sin pixel längs åt vänster
	else if(Diraction_Right == false)
	{
		// Letar vilket block hans längst åt vänster pixeln står på
		int x = (creature.GetPosition_x()) / GameBlockSize;
		int y = (creature.GetPosition_y() + creature.GetTextureSize_y()/2) / GameBlockSize;
		y += 1;		//flyttar ett steg neråt för att få veta vilket block det är under pixeln
		
		int i = y * m_Levels[m_Map_Level].GetMapSize_x() + x;

		// om indixet blir minder 0 eller större än mappen, blir det då 0;
		// Leder till en bugg annars för gubben vet inte vilket block det är på utsidan av banan
		// så vi sätter utsidan blir då 0 som är luft
		if( i > m_Levels[m_Map_Level].GetMapSize_x() * m_Levels[m_Map_Level].GetMapSize_y() ||
			i < 0)
		{
			i = 0;
		}

		//Om blocket är icke stå bart block så ska han byta riktning
		if( m_Levels[m_Map_Level].GetMapData()[i] != 1 &&
			m_Levels[m_Map_Level].GetMapData()[i] != 2 &&
			m_Levels[m_Map_Level].GetMapData()[i] != 3
			)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


void GameFeatures::SetLevel()
{
	m_Map_Level = -1;
	map = new TileMap;
	m_Goal = false;
}

void GameFeatures::SetGoalToTrue()
{
	m_Goal = true;
}

void GameFeatures::SetGoalToFalse()
{
	m_Goal = false;
}

bool GameFeatures::PlayerAtGoal()
{
	return m_Goal;
}