#pragma once
#include <string>
/************************************************************************/
/* 

This is where we define all the character specific gameplay data in a generally flat
nested data structure. 


For each character data type, split it into constant data and mutable data 

struct CharacterData_JumpData_Constants <-- values loaded from file
struct CharacterData_JumpData <-- these values are used in gameplay and are mutable 
*/
/************************************************************************/


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

struct CharacterData_GeneralData
{
	int health;
	//if this is non-zero then this is a force applied to the character while in hit state
	float knockBack; 
};

struct CharacterData_GeneralData_Constants
{
	inline const char * Name(){return name.c_str();}
	inline const int HealthMax(){return healthMax;}
	CharacterData_GeneralData_Constants(char * name, int healthMax); 
private:
	std::string name;
	int healthMax;
};

class CharacterData
{
public:
	CharacterData(CharacterData_GeneralData_Constants generalDataIn, CharacterData_JumpData jumpDataIn);
	~CharacterData(void);
	CharacterData_GeneralData * const MutableData() { return &generalData; } 
	CharacterData_JumpData const * const JumpData() const { return &jumpData; } 
	CharacterData_JumpData_Constants const * const JumpDataConstants() const { return &jumpDataConstants; } 
	CharacterData_GeneralData_Constants const * const GeneralData() const { return &generalDataConstants; }
private:
	//Jump data
	CharacterData_JumpData jumpData;
	CharacterData_JumpData_Constants jumpDataConstants;
	//General data
	CharacterData_GeneralData generalData;
	CharacterData_GeneralData_Constants generalDataConstants;
	
};

