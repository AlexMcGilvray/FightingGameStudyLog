#pragma once
#include "CharacterState.h"
#include "CharacterData.h"
 

namespace CharacterStateFactory
{
	CharacterState * GetCharacterState(CharacterStateType type,Character & character);
	CharacterData * ParseCharacterData(const char * pathToDataDefinition);
}