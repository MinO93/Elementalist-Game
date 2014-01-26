#pragma once
#include <SFML\Graphics.hpp>

class ToolMenu
{
public:
	ToolMenu( sf::Texture * p_Tiles, int p_AmountOfTiles );
	~ToolMenu(void);

	void RenderTiles(sf::RenderTarget& target) const;
	int GetMouseTile( int p_MenuPosition_X, int p_MenuPosition_Y, int p_CurrentMouseTileID );

private:


	void SetTilesPosition();
	sf::RectangleShape m_ToolMenuUI;
	sf::Texture * m_pTiles;
	int m_AmountOfTiles;
	int * TilesPosition_X;
	int * TilesPosition_Y;



	static bool Collision(
	float GameObjekt_Position_x, float GameObjekt_Position_y, 
	float GameObjekt_Size_x,	 float GameObjekt_Size_y, 
	float GameBlock_Position_x,	 float GameBlock_Position_y, 
	float GameBlock_Size_x,		 float GameBlock_Size_y);


};

