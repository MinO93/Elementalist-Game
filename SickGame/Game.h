#pragma once
#include <SFML/Graphics.hpp>



class Game
{
public:
	Game();
	~Game(void);
	void Run();

private:
	sf::Clock m_deltaClock;		// Klocka f�r deltaTiden
	sf::Time TimeTransfer;
	float m_deltaTime;
	sf::View view;	

};

