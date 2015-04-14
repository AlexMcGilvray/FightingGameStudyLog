#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"
#include "../GameData.h"

void State_Jump_Up::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo);
	character.velocityY += character.characterData->JumpData()->yDecay;
	if (character.y >= GameData::LevelGlobalValues::GroundPlaneY())
	{
		character.state.ChangeState(STAND); 
	}
}

void State_Jump_Up::ResetState()
{
	CharacterState::ResetState();
	animation.Reset();
	animation.Start(); 
	character.ZeroVelocity();
	character.velocityY = -character.characterData->JumpDataConstants()->YStartVelocity(); 
}  
