#pragma once
#include "GameSystems.h"

class MenuState : public GameSystems::State
{
public:
	MenuState(void);
	virtual ~MenuState(void);

	virtual void Update();

	virtual void UpdateGUI();

	virtual void Render();

};

