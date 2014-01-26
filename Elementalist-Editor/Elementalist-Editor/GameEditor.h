#pragma once
#include "Tile.h"

class GameEditor
{
public:
	GameEditor(void);
	~GameEditor(void);
	void Run();


private:



	bool m_ToolIsOpen;

	int m_MapSize_X;
	int m_MapSize_Y;
	int * m_TileData;
	
	sf::RenderWindow * window;
	sf::Texture * m_Tiles;

	sf::Sprite m_MouseTile;
	int m_CurrentMouseTileID;



	void LoadStandardMap();
	void LoadAllTilesPictures();
	void RenderAllTiles();
	void ChangeBackgroundTile( int p_MousePosition_X, int p_MousePosition_Y );

	static bool Collision(
	float GameObjekt_Position_x, float GameObjekt_Position_y, 
	float GameObjekt_Size_x,	 float GameObjekt_Size_y, 
	float GameBlock_Position_x,	 float GameBlock_Position_y, 
	float GameBlock_Size_x,		 float GameBlock_Size_y);

};

