#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h" 

void State_Idle::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	character.velocityX = 0;
	character.velocityY = 0;
	if (IsJumpingForward(character,inputInfo))
	{
		character.state.ChangeState(JUMP_FORWARD); 
		return;
	}
	else if (IsJumpingBackwards(character,inputInfo))
	{
		character.state.ChangeState(JUMP_BACKWARD); 
		return;
	}

	if (IsWalkingForward(character,inputInfo))
		character.state.ChangeState(WALKING_FORWARD); 
	else if (IsWalkingBackwards(character,inputInfo))
		character.state.ChangeState(WALKING_BACKWARD);  
	else if (inputInfo.inputMapping[InputValue::BTN1] == InputState::VIRTUAL_KEY_PRESSED) 
		character.state.ChangeState(STAND_ATTACK_1);  


	if (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)
	{ 
		character.state.ChangeState(JUMP_UP); 
	}
	else if (inputInfo.inputMapping[InputValue::DOWN] == InputState::VIRTUAL_KEY_DOWN)
	{ 
		character.state.ChangeState(DUCK);
	} 
}

void State_Idle::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}


