#pragma once
#include "gamesystems.h" 

class Character;
namespace Input
{
	class IController;
} 

class GameState :
	public GameSystems::State
{
public:
	GameState(void);
	virtual ~GameState(void); 
	virtual void Init();
	virtual void Update();
	virtual void UpdateGUI();
	virtual void Render(); 
	Input::IController * controller;
	Input::IController * controller2;
	Character * character;
	Character * character2; 
};

