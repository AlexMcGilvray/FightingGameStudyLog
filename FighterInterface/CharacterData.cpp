#include "CharacterData.h"


CharacterData::CharacterData(CharacterData_GeneralData_Constants generalDataIn, CharacterData_JumpData jumpDataIn):
	generalDataConstants(generalDataIn),
	jumpData(jumpDataIn)
{
}


CharacterData::~CharacterData(void)
{
}

CharacterData_GeneralData_Constants::CharacterData_GeneralData_Constants(char * name, int healthMax):
	name(name),
	healthMax(healthMax)
{
	
}
