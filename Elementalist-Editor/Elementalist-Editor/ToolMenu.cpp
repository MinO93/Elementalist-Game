#include "ToolMenu.h"


ToolMenu::ToolMenu( sf::Texture * p_Tiles, int p_AmountOfTiles ) : 
	m_pTiles(p_Tiles),
	m_AmountOfTiles(p_AmountOfTiles)
{
	SetTilesPosition();
}


ToolMenu::~ToolMenu(void)
{
	delete TilesPosition_X;
	delete TilesPosition_Y;

}

void ToolMenu::RenderTiles(sf::RenderTarget& target)const
{
	sf::Sprite m_CurrentSprite;

	 for( int i = 0; i < m_AmountOfTiles; i++ )
	 {
		 m_CurrentSprite.setTexture( m_pTiles[i] );
		 m_CurrentSprite.setPosition(sf::Vector2f(TilesPosition_X[i], TilesPosition_Y[i]));
		 m_CurrentSprite;

		 target.draw(m_CurrentSprite);
	 }

}

int ToolMenu::GetMouseTile( int p_MenuPosition_X, int p_MenuPosition_Y, int p_CurrentMouseTileID )
{
	for( int i = 0; i < m_AmountOfTiles; i++ )
	 {
		if(Collision(         
		TilesPosition_X[i],
		TilesPosition_Y[i],
		55,
		55,
		p_MenuPosition_X,
		p_MenuPosition_Y,
		1,
		1) == true)
		{
			return i;
		}
	}
	return p_CurrentMouseTileID;
}

void ToolMenu::SetTilesPosition()
{
	 TilesPosition_X = new int[m_AmountOfTiles];
	 TilesPosition_Y = new int[m_AmountOfTiles];

	 int x = 25;
	 int y = 25;

	 for( int i = 0; i < m_AmountOfTiles; i++ )
	 {
		 TilesPosition_X[i] = x;
		 TilesPosition_Y[i] = y;

		 x += 75;
		 if(75 * 5 < x )
		 {
			 x = 25;
			 y += 75;
		 }
	 }
}


bool ToolMenu::Collision(
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