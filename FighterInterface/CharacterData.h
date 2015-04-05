#pragma once

//TODO, for each character data type, split it into constants and mutables ex
// struct CharacterData_JumpData_Constants <-- values loaded from file
// struct CharacterData_JumpData <-- these values are used in gameplay and are mutable

struct CharacterData_JumpData_Constants
{ 
	inline float XVelocityDefault(){ return xVelocity; }
	inline float YStartVelocity(){ return yStartVelocity; }
	inline float YDecay(){ return yDecay; }
	inline float GravityMultiplier(){ return gravityMultiplier; }
private:
	float xVelocity;
	float yStartVelocity;
	float yDecay;
	float gravityMultiplier;
};

struct CharacterData_JumpData
{
	float xVelocity;
	float yStartVelocity;
	float yDecay;
	float gravityMultiplier;
};

struct CharacterData_MutableData
{
	int health;
	//if this is non-zero then this is a force applied to the character (used when they are hit)
	float knockBack; 
};

struct CharacterData_GeneralData
{
	char * name;
	//int healthMax
	//float knockbackReduction
};

class CharacterData
{
public:
	CharacterData(CharacterData_GeneralData generalDataIn, CharacterData_JumpData jumpDataIn);
	~CharacterData(void);
	CharacterData_MutableData * const MutableData() { return &mutableData; } 
	CharacterData_JumpData const * const JumpData() const { return &jumpData; } 
	CharacterData_GeneralData const * const GeneralData() const { return &generalData; }
private:
	CharacterData_JumpData jumpData;
	CharacterData_MutableData mutableData;
	CharacterData_GeneralData generalData;
};

