#include "GameEditor.h"

#include <iostream>
#include "ToolMenu.h"

const int GameWindowSize_x = 1400;
const int GameWindowSize_y = 800;
const int GameBlockSize = 55;


GameEditor::GameEditor(void) :
	m_ToolIsOpen(true),
	m_MapSize_X(14),
	m_MapSize_Y(10),
	m_CurrentMouseTileID(0)
{
}


GameEditor::~GameEditor(void)
{
	delete m_TileData;
	delete []m_Tiles;
	delete window;
}

void GameEditor::Run()
{

	LoadAllTilesPictures();
	LoadStandardMap();


	window = new sf::RenderWindow(sf::VideoMode(GameWindowSize_x, GameWindowSize_y), "Elementalist");

	m_MouseTile.setTexture(m_Tiles[m_CurrentMouseTileID]);
	m_MouseTile.setPosition(500,500);
	

	ToolMenu toolmenu( m_Tiles, 14 ) ;



	sf::View GameView(sf::FloatRect(0, 0, 1400, 800));
	sf::View ToolMenyView(sf::FloatRect(0, 0, 1400, 800));



	// Ritar en Triangel

	sf::RectangleShape ToolRectangle(sf::Vector2f(400, 800));
	ToolRectangle.setFillColor(sf::Color::Black);




    // run the program as long as the window is open
    while (window->isOpen())
    {
		// check all the window's events that were triggered since the last iteration of the loop
       
        while (window->pollEvent(mEvent))
        {
            // "close requested" event: we close the window
            if (mEvent.type == sf::Event::Closed)
                window->close();

			if(mEvent.type == sf::Event::KeyPressed )
			{
				if(mEvent.key.code == sf::Keyboard::Q)
				{
					if(m_ToolIsOpen == true)
					{
						m_ToolIsOpen = false,
						ToolRectangle.setPosition(-400,0);
					}
					else if(m_ToolIsOpen == false)
					{
						m_ToolIsOpen = true;
						ToolRectangle.setPosition(0,0);
					}
				}
			}
			
			

			if (mEvent.type == sf::Event::MouseButtonPressed)
			{
				if (mEvent.mouseButton.button == sf::Mouse::Right)
				{

					int BlockID_X = mEvent.mouseButton.x / GameBlockSize;
					int BlockID_Y = mEvent.mouseButton.y / GameBlockSize;

					std::cout << "the right button was pressed" << std::endl;
					std::cout << "BlockID_X: " << BlockID_X << std::endl;
					std::cout << "BlockID_Y: " << BlockID_Y << std::endl;
				}

				if( m_ToolIsOpen == true && mEvent.mouseButton.button == sf::Mouse::Left)
				{
					if(Collision(         
						ToolRectangle.getPosition().x,
						ToolRectangle.getPosition().y,
						ToolRectangle.getSize().x,
						ToolRectangle.getSize().y,
						mEvent.mouseButton.x,
						mEvent.mouseButton.y,
						1,
						1) == true)
					{
						m_CurrentMouseTileID = toolmenu.GetMouseTile (mEvent.mouseButton.x, mEvent.mouseButton.y, m_CurrentMouseTileID );
						m_MouseTile.setTexture(m_Tiles[m_CurrentMouseTileID]);	
					}
					else if(mEvent.mouseButton.button == sf::Mouse::Left)
					{
						ChangeBackgroundTile(mEvent.mouseButton.x, mEvent.mouseButton.y);
					}
				}
				else if(mEvent.mouseButton.button == sf::Mouse::Left)
				{
					ChangeBackgroundTile(mEvent.mouseButton.x, mEvent.mouseButton.y);
				}
			}




			// End of the Press-Buttons
		}

		//////////////////////////////////////////////////
		// Update ////////////////////////////////////////
		//////////////////////////////////////////////////

		if (mEvent.type == sf::Event::MouseMoved)
			{
				m_MouseTile.setPosition(sf::Vector2f(mEvent.mouseMove.x - GameBlockSize/2, mEvent.mouseMove.y - GameBlockSize/2));
			}

		if( mEvent.type == sf::Event::MouseMoved
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) 
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)
				)
			{
				if(m_ToolIsOpen == false)
				{
					ChangeBackgroundTile(mEvent.mouseMove.x, mEvent.mouseMove.y);
				}
			}

		
		//////////////////////////////////////////////////
		// Render ////////////////////////////////////////
		//////////////////////////////////////////////////

        // clear the window with black color
		window->clear(sf::Color::Black);
	
        // draw everything here...
		
		window->setView(GameView);
		RenderAllTiles();
		

		window->setView(ToolMenyView);
		window->draw(ToolRectangle);

		if(m_ToolIsOpen == true)
		{
			toolmenu.RenderTiles(*window);
		}
		window->draw(m_MouseTile);
		AreaBigBuildLine();

        // end the current frame
        window->display();
    }



}


void GameEditor::LoadAllTilesPictures()
{
	int AmountOfTiles = 14;
	int AmountTilesOnRoad_X = 10;

	m_Tiles = new sf::Texture[ AmountOfTiles ];

	int x = 0;
	int y = 0;

	// Laddar in Alla tiles
	for(int i = 0; i < AmountOfTiles; i++)
	{
		m_Tiles[i].loadFromFile("Pictures/tidesheet1.1.png", sf::IntRect(GameBlockSize*x, GameBlockSize*y, GameBlockSize, GameBlockSize));

		x++;
		if( x >= AmountTilesOnRoad_X)
		{
			x = 0;
			y++;
		}
	}
}

void GameEditor::LoadStandardMap()
{
	m_TileData	= new int[ m_MapSize_X * m_MapSize_Y ];

	for( int i = 0; i < m_MapSize_X * m_MapSize_Y; i++ )
	{
		m_TileData[i] = 0;
		if( i > (m_MapSize_X * (m_MapSize_Y-2) - 1))
		{
			m_TileData[i] = 2;
			if( i > (m_MapSize_X * (m_MapSize_Y-1) - 1))
			{
				m_TileData[i] = 1;
			}
		}
	}
}

void GameEditor::RenderAllTiles()
{
	int BlockPosition_X = 0;
	int BlockPosition_Y = 0;

	for( int i = 0; i < m_MapSize_X * m_MapSize_Y; i++ )
	{
		int x = m_TileData[i];	

		sf::Sprite CurrentBlock;
		CurrentBlock.setTexture(m_Tiles[x]);
		CurrentBlock.setPosition(sf::Vector2f(GameBlockSize * BlockPosition_X, GameBlockSize * BlockPosition_Y));
		window->draw(CurrentBlock);

		BlockPosition_X++;
			
		if( BlockPosition_X >= m_MapSize_X)
		{
			BlockPosition_X = 0;
			BlockPosition_Y++;
		}
	}
		
}

void GameEditor::ChangeBackgroundTile( int p_MousePosition_X, int p_MousePosition_Y )
{
	int BlockID_X = p_MousePosition_X / GameBlockSize;
	int BlockID_Y = p_MousePosition_Y / GameBlockSize;

	int BlockID = ( BlockID_Y * m_MapSize_X) + BlockID_X;

	if(BlockID >= 0 
	&& BlockID < m_MapSize_X * m_MapSize_Y
	&& BlockID_X <= m_MapSize_X - 1
	)
	{
		m_TileData[BlockID] = m_CurrentMouseTileID;
	}

}

void GameEditor::AreaBigBuildLine()
{

	if ( mEvent.type == sf::Event::MouseButtonPressed )
	{
		if (mEvent.mouseButton.button == sf::Mouse::Right && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			int BlockID_X = mEvent.mouseButton.x / 55;
			int BlockID_Y = mEvent.mouseButton.y / 55;


			m_AreaBigBuildLine_StartPosition = sf::Vector2f( (BlockID_X * 55 ) + 25, ( BlockID_Y * 55 ) + 25 );
			m_AreaBigBuildLine[0].position = m_AreaBigBuildLine_StartPosition;
			m_AreaBigBuildLine[1].position = m_AreaBigBuildLine_StartPosition;

		}
	}
	

	// Bugg här, Den ''funktionen'' under här kan ibland göra före den andra där uppe
	// För in en bool som säger till att att start punkten har skapat för den nya AreaBigBuildLine punkten.


	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
	
		if (mEvent.type == sf::Event::MouseMoved)
		{
			m_AreaBigBuildLine[1].position = sf::Vector2f( mEvent.mouseMove.x, mEvent.mouseMove.y );
		}

		window->draw(m_AreaBigBuildLine, 2, sf::Lines);
	}

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mEvent.mouseButton.button == sf::Mouse::Right)
	{
		int katt = 5;
		int fisk = 5;
	}

	


}

bool GameEditor::Collision(
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
