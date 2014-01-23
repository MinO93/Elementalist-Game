#pragma once
#include "Class.h"
#include "TileMap.h"

class Creature;
class Level;


class GameFeatures
{
public:
	GameFeatures(void);
	~GameFeatures(void);

	static void LoadImages();
	static void CloseImages();

	static void Update(float deltaTime);
	static void Display(sf::RenderWindow *window);
	static sf::Vector2f CameraUpdate(int GameWindowSize_x, int GameWindowSize_y);

	static void Initialize();
	static void DeleteObjektsBeforeExitGame();
	static void EraseAllObjekts();
	static void DamageDealerFunction(AbilityObjekt *abilityobjekt);	
	static bool TurnEnemyDiraction(Creature &creature, bool Diraction_Right);

	//Create Creature
	static void Create_Player(int spelare);
	static void Set_PlayerPosition(int x, int y);
	static void SpawnEntities();
	static void Create_Enemy(int x, int y, int creature_select);
	
	//Spells
	static void Create_StandardWind(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction);
	static void Create_FireBolt(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction);
	static void Create_IceBolt(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction);
	static void Create_MeleeAttack(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, int TextureSize_x, int TextureSize_y, Faction faction);
	static void Create_FrostNova(bool Diraction_Right, int Owners_Position_x, int Owners_Position_y, Faction faction, int NumberOfIceCubes);

	//Collisions
	static bool Check_Collision_With_StandardBlocks(Creature &creature);
	static bool Check_Collision_With_StandardBlocks(AbilityObjekt *abilityobjekt);
	
	static bool Collision(
	float GameObjekt_Position_x, float GameObjekt_Position_y, 
	float GameObjekt_Size_x,	 float GameObjekt_Size_y, 
	float GameBlock_Position_x,	 float GameBlock_Position_y, 
	float GameBlock_Size_x,		 float GameBlock_Size_y);

	// Map stuffs
	static void SetGoalPosition();
	static void LoadMap();
	static void LoadTileMap();
	static void InitializeNextLevel();
	
	static bool PlayerAtGoal();
	static void SetGoalToTrue();
	static void SetGoalToFalse();
	static void SetLevel();

private:
	static void KillObjekt();


};

