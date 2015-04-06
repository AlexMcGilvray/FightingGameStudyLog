#pragma once

#include "CharacterState.h"

class State_Idle : CharacterState
{ 
public:
	State_Idle(Character & character,CharacterStateAnimation anim, const char * name )  : 
		CharacterState(character,anim,name) { }

	virtual void UpdateState(InputInfo & inputInfo) override; 
	virtual void ResetState() override;

};
