#pragma once

bool IsWalkingForward(const Character &  character, const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::LEFT)) || 
		((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::RIGHT)) ;
}

bool IsWalkingBackwards(const Character &  character,const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::RIGHT)) || 
		((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::LEFT)) ;
}


bool IsJumpingForward(const Character &  character,const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::LEFT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) 
		|| 
		((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::RIGHT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) ;
}

bool IsJumpingBackwards(const Character &  character, const InputInfo &  inputInfo)
{
	return	((inputInfo.inputMapping[InputValue::LEFT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::RIGHT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) 
		|| 
		((inputInfo.inputMapping[InputValue::RIGHT] == InputState::VIRTUAL_KEY_DOWN) && 
		(character.Facing() == CharacterFacing::LEFT) && (inputInfo.inputMapping[InputValue::UP] == InputState::VIRTUAL_KEY_DOWN)) ;
}
