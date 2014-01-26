#include "Game.h"
#include "GameFeatures.h"

#include "MemoryLeak.h"

const int GameWindowSize_x = 1400;
const int GameWindowSize_y = 800;

static const float Zoom = 1;

static const int AreaCheck = 1;

Game::Game()
{
	GameFeatures::SetLevel();
	view.setSize(sf::Vector2f(GameWindowSize_x/Zoom, GameWindowSize_y/Zoom));
}


Game::~Game(void)
{
	GameFeatures::EraseAllObjekts();
	GameFeatures::CloseImages();
	GameFeatures::DeleteObjektsBeforeExitGame();
}


void Game::Run()
{
	sf::RenderWindow window(sf::VideoMode(GameWindowSize_x, GameWindowSize_y), "Elementalist");


	//Laddar in alla banor som ligger i mappen "Map"
	GameFeatures::LoadMap();		
	
	//Laddar in alla bilder
	GameFeatures::Create_Player(0);
	GameFeatures::Create_Player(1);
	GameFeatures::LoadImages();	// Laddar in även två ljud

    // run the main loop
    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
		//Nästa level öppnas
		GameFeatures::InitializeNextLevel();

		//Stage loop
		while (GameFeatures::PlayerAtGoal() == false && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			// handle events
			sf::Event event;
			bool a = false;
			while (window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					window.close();
				}
				if(event.type == sf::Event::KeyPressed) {
					if(event.key.code == sf::Keyboard::O) {
						GameFeatures::SetGoalToTrue();
						a = true;
					} 
				}
			}
			if(a) break;
		
			/////////////////////////////////////////////
			////////		 DeltaTimer			/////////
			/////////////////////////////////////////////
			TimeTransfer = m_deltaClock.getElapsedTime();
			m_deltaTime = TimeTransfer.asSeconds();
			m_deltaClock.restart();

			if(m_deltaTime > 0.1)
			{
				m_deltaTime = 0.1;
			}
	

			/////////////////////////////////////////////
			////////	 Uppdaterar Objekten	/////////
			/////////////////////////////////////////////
			GameFeatures::Update(m_deltaTime);

			/////////////////////////////////////////////
			////////	 Uppdaterar Kameran		/////////
			/////////////////////////////////////////////
			view.setCenter(GameFeatures::CameraUpdate(GameWindowSize_x/Zoom, GameWindowSize_y/Zoom ));	// Kameran sätts på spelaren													
			window.setView(view);		// Fönstret använder Kameran som bild
			

			//////////////////////////////////////////////
			//	Väljer vilka objekt som ska ritas ut	//
			//////////////////////////////////////////////
			window.clear();	
			GameFeatures::Display(&window);		//Ritar ut alla Objekt
			
			//////////////////////////////////////////////
			//	Ritar ut det vi har valt som ska ritas	//
			//////////////////////////////////////////////
			window.display();

			
		

		}
		//Detta sker efter spelaren har klarat leveln
		GameFeatures::EraseAllObjekts();
	}

}