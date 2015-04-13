#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"

void State_WalkingBackward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
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

	float xVel = character.characterData->MovementConstants()->XVelocityDefault();

	if (IsWalkingBackwards(character,inputInfo))
	{
		if (character.Facing() == CharacterFacing::LEFT)
			character.velocityX = xVel;
		else
			character.velocityX = -xVel; 
	} 
	else if (IsWalkingForward(character,inputInfo))
	{
		character.state.ChangeState(WALKING_FORWARD);  
		return;
	} 
	else
	{
		character.state.ChangeState(STAND); 
		return;
	}
}

void State_WalkingBackward::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  