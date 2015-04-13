#include "CharacterUtils.h"
#include "../CharacterStates.h"
#include "../CharacterState.h"
#include "../GameData.h"
#include "../Debug.h"
#include "../Utilities.h"

void State_Jump_Forward::UpdateState(InputInfo & inputInfo)
{
	CharacterState::UpdateState(inputInfo); 
	character.velocityY += character.characterData->JumpData()->yDecay;  
	if (character.y >= GameData::LevelGlobalValues::GroundPlaneY())
	{ 
		character.state.ChangeState(STAND); 
	}
}

void State_Jump_Forward::ResetState()
{ 
	CharacterState::ResetState();
	animation.Reset();
	animation.Start(); 

	character.velocityY = -character.characterData->JumpData()->yStartVelocity;  
	if (character.Facing() == CharacterFacing::LEFT)
		character.velocityX = -character.characterData->JumpData()->xVelocity;
	else
		character.velocityX = character.characterData->JumpData()->xVelocity;

	std::string str = Utilities::GetFormattedString(
		"jump forward with start vel of %f and xVel of %f",
		character.velocityY,
		character.velocityX);
	Debug::Logger::Log(str);
}