#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"

void State_StandAttack1::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	if (animation.Complete())
	{
		character.state.ChangeState(STAND);
	}
	else
	{
		character.velocityX = 0;
		character.velocityY = 0; 
	} 
}

void State_StandAttack1::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}
