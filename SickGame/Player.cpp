#include "Player.h"
#include "GameFeatures.h"

#include "MemoryLeak.h"

static sf::Sound JumpSound;
static sf::SoundBuffer JumpFile;

static sf::Sound TakeDamageSound;
static sf::SoundBuffer TakeDamageFile;

static int	TextureSize_x(256/8);
static int	TextureSize_y(288/6);

static float GravityValue = 18 * 1.1;			//Hur högt Gubben hoppar (Oberoende hur snabbt han hoppar)
static float GravitySpeed = 200 * 1.1;		//Hur snabbt han hoppar och faller
static float MovementSpeed = 175 * 1.1;

static int StartHealth = 100;

static int HealthBar_x = 50;
static int HealthBar_y = 10;
static int HealthBarOutlineThickness = 2;
static int SpecialAbilityBar_y = 3;

static const int AreaCheck = 1;

Player::Player(int spelare) :
	MageSpecialiaztionIndex(0),
	faction (FRIEND),
	m_IsAlive(true),
	Joystick_Change_Mage(true),
	m_JoyStickPlayer(spelare)
{
	mage[0] = new FireMage;
	mage[1] = new FrostMage;
	mage[2] = new AirMage;
	m_physics = new Physics(sprite, this, MovementSpeed);

	HealthBar.setSize(sf::Vector2f(HealthBar_x, HealthBar_y));
	HealthBar.setOrigin(sf::Vector2f());

	SpecialAbilityBar.setSize(sf::Vector2f(HealthBar_x, SpecialAbilityBar_y));
	SpecialAbilityBar.setFillColor(sf::Color(200, 200, 0, 150));
	SpecialAbilityBar.setOrigin(sf::Vector2f());

	if(m_JoyStickPlayer == 0)
	{
		HealthBar.setFillColor(sf::Color(0, 255, 0, 150));
	}
	if(m_JoyStickPlayer == 1)
	{
		HealthBar.setFillColor(sf::Color(255, 0, 0, 150));
	}


	HealthBarBlackFrame = HealthBar;
	HealthBarBlackFrame.setOutlineColor(sf::Color(0, 0, 0, 150));
	HealthBarBlackFrame.setOutlineThickness(HealthBarOutlineThickness);
	HealthBarBlackFrame.setFillColor(sf::Color(0, 0, 0, 0));

	SpecialAbilityBarBlackFrame = SpecialAbilityBar;
	SpecialAbilityBarBlackFrame.setOutlineColor(sf::Color(0, 0, 0, 150));
	SpecialAbilityBarBlackFrame.setOutlineThickness(HealthBarOutlineThickness);
	SpecialAbilityBarBlackFrame.setFillColor(sf::Color(0, 0, 0, 0));
}


Player::~Player(void)
{
	delete m_physics;
	delete mage[0];
	delete mage[1];
	delete mage[2];
}

void Player::initilize()
{

	if(m_JoyStickPlayer == 0)
	{
		HealthBar.setFillColor(sf::Color(0, 255, 0, 150));
	}
	if(m_JoyStickPlayer == 1)
	{
		HealthBar.setFillColor(sf::Color(255, 0, 0, 150));
	}

	m_physics->ResetValues();
	PlayerTexture = mage[MageSpecialiaztionIndex]->StandingRight();
	sprite.setTexture(*PlayerTexture);
	sprite.setOrigin(sf::Vector2f(0, 0));
	m_HealthPoints = StartHealth;
	sprite.setPosition(sf::Vector2f(m_SpawnPosition_x, m_SpawnPosition_y));
	m_Diraction_Right = true;
	C_StandardSpell.restart();
	SpecialAbility_timer = 5;
	m_IsAlive = true;
}

void Player::LoadSound()
{
	JumpFile.loadFromFile("Audio/jump.wav");
	JumpSound.setBuffer(JumpFile);
	JumpSound.setPitch(5);

	TakeDamageFile.loadFromFile("Audio/ajajaj.wav");
	TakeDamageSound.setBuffer(TakeDamageFile);
	TakeDamageSound.setPlayingOffset(sf::seconds(0));
}

void Player::Update(float deltaTime)
{
	HealthBar.setPosition(sf::Vector2f((sprite.getPosition().x + TextureSize_x/2) -HealthBar_x/2, sprite.getPosition().y-20));
	HealthBar.setSize(sf::Vector2f(m_HealthPoints/2, HealthBar_y));
	HealthBarBlackFrame.setPosition(sf::Vector2f((sprite.getPosition().x + TextureSize_x/2) -HealthBar_x/2, sprite.getPosition().y-20));

	int SpecialAbilitySizeBar = SpecialAbility_timer * 10;
	if (SpecialAbilitySizeBar > 50){ SpecialAbilitySizeBar = 50; }
	SpecialAbilityBar.setSize(sf::Vector2f(SpecialAbilitySizeBar, SpecialAbilityBar_y));
	SpecialAbilityBar.setPosition(HealthBarBlackFrame.getPosition() + sf::Vector2f( 0, HealthBar_y + HealthBarOutlineThickness ));
	SpecialAbilityBarBlackFrame.setPosition(HealthBarBlackFrame.getPosition() + sf::Vector2f( 0, HealthBar_y + HealthBarOutlineThickness ));

	if(!sf::Joystick::isButtonPressed(m_JoyStickPlayer, 4) && !sf::Joystick::isButtonPressed(m_JoyStickPlayer, 5))
	{
		Joystick_Change_Mage = true;
	}

	if( m_HealthPoints <= 0)
	{
		m_IsAlive = false;
	}

	if(m_physics->Get_AffectedByIce() == false && m_physics->Get_Immobilize() == false)
	{
		HealthBar.setFillColor(sf::Color(0, 255, 0, 150));
	}

	Fire();
	ChangeMageSpecialiaztion();
	Animations(deltaTime);
	m_physics->Update(deltaTime);

	for(int i = 0; 5 > i; i++)
	{
		PlayerMovement(deltaTime/5);
	}

	SpecialAbility_timer += deltaTime;
	
}

void Player::PlayerMovement(float deltaTime)
{
	Joystick_x_value = sf::Joystick::getAxisPosition(m_JoyStickPlayer, sf::Joystick::X);

	m_physics->MoveDown(deltaTime);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || Joystick_x_value < -50)
	{
		m_physics->MoveLeft( deltaTime );
		m_Diraction_Right = false;
		m_AnimationTimer += 5000*deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || Joystick_x_value > 50)
	{
		m_physics->MoveRight( deltaTime );
		m_Diraction_Right = true;
		m_AnimationTimer += 5000*deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(m_JoyStickPlayer, 0))
	{
		if(m_physics->Get_inAir() == false)
		{
			JumpSound.play();
			m_physics->MoveUp( deltaTime );
		}
	}
}



void Player::GetHitByWind(int windspeed)
{
	m_physics->GetHitByWind(windspeed);
}

void Player::GetHitByIce(int ElementPower)
{
	m_physics->GetHitByIce(ElementPower);
	HealthBar.setFillColor(sf::Color(0, 0, 255, 150));
}


void Player::Animations(float deltaTime)
{

		if(		m_AnimationTimer < 500	&& m_Diraction_Right == false)	{ PlayerTexture = mage[MageSpecialiaztionIndex]->RunningLeft1(); }
		else if(m_AnimationTimer < 1000	&& m_Diraction_Right == false)	{ PlayerTexture = mage[MageSpecialiaztionIndex]->StandingLeft(); }
		else if(m_AnimationTimer < 1500	&& m_Diraction_Right == false)	{ PlayerTexture = mage[MageSpecialiaztionIndex]->RunningLeft2(); }
		else if(m_AnimationTimer < 2000	&& m_Diraction_Right == false)	{ PlayerTexture = mage[MageSpecialiaztionIndex]->StandingLeft(); }
		
		if(		m_AnimationTimer < 500 	&& m_Diraction_Right == true) { PlayerTexture = mage[MageSpecialiaztionIndex]->RunningRight1(); }
		else if(m_AnimationTimer < 1000	&& m_Diraction_Right == true) { PlayerTexture = mage[MageSpecialiaztionIndex]->StandingRight(); }
		else if(m_AnimationTimer < 1500	&& m_Diraction_Right == true) { PlayerTexture = mage[MageSpecialiaztionIndex]->RunningRight2(); }
		else if(m_AnimationTimer < 2000	&& m_Diraction_Right == true) { PlayerTexture = mage[MageSpecialiaztionIndex]->StandingRight(); }

		if(m_AnimationTimer > 2500)	{ m_AnimationTimer = 0; }
	

		// När inte någon Piltagent är nere så byter gubben till stå bild, istället för spring bild
		if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && 
			(Joystick_x_value  < 50  && Joystick_x_value > -50))
		{
			if(m_Diraction_Right == false)		{ PlayerTexture = mage[MageSpecialiaztionIndex]->StandingLeft(); }
			else if(m_Diraction_Right == true)	{ PlayerTexture = mage[MageSpecialiaztionIndex]->StandingRight(); }
			m_AnimationTimer = 0;
		}

		sprite.setTexture(*PlayerTexture);
}


float Player::GetPosition_x()const
{
	return sprite.getPosition().x;
}

float Player::GetPosition_y()const
{
	return sprite.getPosition().y;
}

void Player::SetPosition(float position_x, float position_y)
{
	m_SpawnPosition_x = position_x;
	m_SpawnPosition_y = position_y;
}

void Player::Fire()
{
	sf::Time timer = C_StandardSpell.getElapsedTime();
	Joystick_Z_value = sf::Joystick::getAxisPosition(m_JoyStickPlayer, sf::Joystick::Z);
	
	if (( sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Joystick::isButtonPressed(m_JoyStickPlayer, 1) || Joystick_Z_value < -50 )&&   timer.asSeconds() > 0.5)
	{
		C_StandardSpell.restart();
		mage[MageSpecialiaztionIndex]->StandardSpell(m_Diraction_Right, GetPosition_x(), GetPosition_y(), faction);
	}

	if (( sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Joystick::isButtonPressed(m_JoyStickPlayer, 3) ) &&   SpecialAbility_timer > 5)
	{
		SpecialAbility_timer = 0;
		mage[MageSpecialiaztionIndex]->SpecialAbility(m_Diraction_Right, GetPosition_x(), GetPosition_y(), faction);
	}



}

void Player::ReceiveDamage(int damage)
{
	if(m_physics->Get_AffectedByIce() == true)
	{
		m_HealthPoints -= damage * 2;
	}
	else
	{
		m_HealthPoints -= damage;
	}

	if(damage > 0)
	{
		TakeDamageSound.play();
	}
}

int Player::GetTextureSize_x()const
{
	return mage[MageSpecialiaztionIndex]->GetTextureSize_x();
}

int Player::GetTextureSize_y()const
{
	return mage[MageSpecialiaztionIndex]->GetTextureSize_y();
}

bool Player::IsAlive()const
{
	return m_IsAlive;
}

void Player::ChangeMageSpecialiaztion()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		MageSpecialiaztionIndex = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		MageSpecialiaztionIndex = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		MageSpecialiaztionIndex = 2;
	}

	if(sf::Joystick::isButtonPressed(m_JoyStickPlayer, 4) && Joystick_Change_Mage == true)
	{
		Joystick_Change_Mage = false;
		MageSpecialiaztionIndex++;
		if(MageSpecialiaztionIndex > 2) { MageSpecialiaztionIndex = 0;}
	}
	if(sf::Joystick::isButtonPressed(m_JoyStickPlayer, 5) && Joystick_Change_Mage == true)
	{
		Joystick_Change_Mage = false;
		MageSpecialiaztionIndex--;
		if(MageSpecialiaztionIndex < 0) { MageSpecialiaztionIndex = 2;}
	}
}



