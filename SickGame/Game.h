#pragma once
#include <SFML/Graphics.hpp>



class Game
{
public:
	Game();
	~Game(void);
	void Run();

private:
	sf::Clock m_deltaClock;		// Klocka för deltaTiden
	sf::Time TimeTransfer;
	float m_deltaTime;
	sf::View view;	

};

