#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics.hpp>

enum Element {FIRE, WATER, ICE,  WIND, EARTH, NEUTRAL, MELEE};
enum Faction {FRIEND, ENEMY, FRIENDLYFIRE};

class AbilityObjekt : public sf::Drawable
{
public:
	virtual ~AbilityObjekt(void);
	virtual void Update(float deltaTime) = 0;
	virtual bool IsAlive() = 0;
	virtual void KillObjekt() = 0;
	virtual int GetPosition_x()const = 0;
	virtual int GetPosition_y()const = 0;
	virtual int GetTextureSize_x()const = 0;
	virtual int GetTextureSize_y()const = 0;
	virtual int GetDamage()const = 0;
	virtual Element GetElement()const = 0;
	virtual Faction GetFaction()const = 0;
	virtual int GetSpeed()const = 0;
	virtual int GetElementPower()const = 0;
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

