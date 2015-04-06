#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"
#include "../GameData.h"

void State_Jump_Backward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	character.velocityY += character.characterData->JumpData()->yDecay;  
	if (character.y >= GameData::LevelGlobalValues::GroundPlaneY())
	{ 
		character.state.ChangeState(STAND); 
	}
}

void State_Jump_Backward::ResetState()
{
	CharacterState::ResetState();
	character.velocityY = -character.characterData->JumpData()->yStartVelocity;  
	if (character.Facing() == CharacterFacing::LEFT)
		character.velocityX = character.characterData->JumpData()->xVelocity;
	else
		character.velocityX = -character.characterData->JumpData()->xVelocity;
}  