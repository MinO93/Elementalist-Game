#pragma once
#include <SFML\Graphics.hpp>

class Tile 
{
public:
	Tile(void);
	~Tile(void);


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_Sprite, states);
    }

	sf::Sprite m_Sprite;
	
	


};

