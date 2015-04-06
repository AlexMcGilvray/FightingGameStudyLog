#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"

void State_HitStun::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	CharacterData_GeneralData * mData = character.characterData->MutableData();
	if (animation.Complete())
	{
		mData->knockBack = 0;
		character.state.PopState();
	}
	else
	{
		if (character.Facing() == CharacterFacing::LEFT)
		{
			character.velocityX = mData->knockBack;
		}
		else
		{
			character.velocityX = -mData->knockBack;
		}
	} 
}

void State_HitStun::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start();
}  