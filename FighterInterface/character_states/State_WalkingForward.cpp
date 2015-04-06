#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"

void State_WalkingForward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	if (IsJumpingForward(character,inputInfo))
		character.state.ChangeState(JUMP_FORWARD); 
	else if (IsJumpingBackwards(character,inputInfo))
		character.state.ChangeState(JUMP_BACKWARD); 

	if (IsWalkingForward(character,inputInfo))
	{
		if (character.Facing() == CharacterFacing::LEFT)
			character.velocityX = -0.1f; //TODO this needs to be data driven
		else
			character.velocityX = 0.1f; 
	} 
	else if (IsWalkingBackwards(character,inputInfo))
	{
		character.state.ChangeState(WALKING_BACKWARD);  
	} 
	else
	{
		character.state.ChangeState(STAND); 
	} 
}

void State_WalkingForward::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  