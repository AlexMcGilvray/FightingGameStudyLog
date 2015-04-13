#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h" 

void State_WalkingForward::UpdateState(InputInfo & inputInfo)
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

	if (IsWalkingForward(character,inputInfo))
	{
		if (character.Facing() == CharacterFacing::LEFT)
			character.velocityX = -xVel;
		else
			character.velocityX = xVel; 
	} 
	else if (IsWalkingBackwards(character,inputInfo))
	{
		character.state.ChangeState(WALKING_BACKWARD);  
		return;
	} 
	else
	{
		character.state.ChangeState(STAND); 
		return;
	} 
}

void State_WalkingForward::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  