#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"

void State_WalkingBackward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	if (IsJumpingForward(character,inputInfo))
		character.state.ChangeState(JUMP_FORWARD); 
	else if (IsJumpingBackwards(character,inputInfo))
		character.state.ChangeState(JUMP_BACKWARD); 

	if (IsWalkingBackwards(character,inputInfo))
	{
		if (character.Facing() == CharacterFacing::LEFT)
			character.velocityX = 0.1f;
		else
			character.velocityX = -0.1f; 
	} 
	else if (IsWalkingForward(character,inputInfo))
	{
		character.state.ChangeState(WALKING_FORWARD);  
	} 
	else
	{
		character.state.ChangeState(STAND); 
	}
}

void State_WalkingBackward::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  