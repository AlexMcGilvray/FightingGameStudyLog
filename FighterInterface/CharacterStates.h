#pragma once 
#include "CharacterState.h"

class State_Idle : CharacterState
{ 
public:
	State_Idle(Character & character,CharacterStateAnimation anim, const char * name )  : 
		CharacterState(character,anim,name) { }

	virtual void UpdateState(InputInfo & inputInfo) override; 
	virtual void ResetState() override;

};


class State_Duck : CharacterState
{ 
public:
	State_Duck(Character & character,CharacterStateAnimation anim, const char * name )  : 
		CharacterState(character,anim,name) { }

	virtual void UpdateState(InputInfo & inputInfo) override; 
	virtual void ResetState() override;

};

class State_StandAttack1 : CharacterState
{ 
public:
	State_StandAttack1(Character & character,CharacterStateAnimation anim, const char * name ) : 
		CharacterState(character,anim,name) { }

	virtual void UpdateState(InputInfo & inputInfo) override;  
	virtual void ResetState() override; 

};

class State_WalkingForward : CharacterState
{ 
public:
	State_WalkingForward(Character & character,CharacterStateAnimation anim, const char * name )  : 
		CharacterState(character,anim,name) { }

	virtual void UpdateState(InputInfo & inputInfo) override;  
	virtual void ResetState() override; 
};

class State_WalkingBackward : CharacterState
{ 
public:
	State_WalkingBackward(Character & character,CharacterStateAnimation anim, const char * name)  : 
		CharacterState(character,anim,name) { }

	virtual void UpdateState(InputInfo & inputInfo) override;   
	virtual void ResetState() override;  
};

class State_HitStun : CharacterState
{ 
public:
	State_HitStun(Character & character,CharacterStateAnimation anim, const char * name)  : 
		CharacterState(character,anim,name) { }

	virtual void UpdateState(InputInfo & inputInfo) override;
	virtual void ResetState() override;  
};

class State_Jump_Up : CharacterState
{ 
public:
	State_Jump_Up(Character & character,CharacterStateAnimation anim, const char * name)  : 
		CharacterState(character,anim,name)
	{
		AffectedByGravity(false);
	}

	virtual void UpdateState(InputInfo & inputInfo) override; 
	virtual void ResetState() override;
private: 
};

class State_Jump_Forward : CharacterState
{ 
public:
	State_Jump_Forward(Character & character,CharacterStateAnimation anim, const char * name)  : 
		CharacterState(character,anim,name)
	{
		AffectedByGravity(false);
	}

	virtual void UpdateState(InputInfo & inputInfo) override;  
	virtual void ResetState() override; 
private: 
};

class State_Jump_Backward : CharacterState
{ 
public:
	State_Jump_Backward(Character & character,CharacterStateAnimation anim, const char * name)  : 
		CharacterState(character,anim,name)
	{
		AffectedByGravity(false);
	}

	virtual void UpdateState(InputInfo & inputInfo) override;   
	virtual void ResetState() override;  
private: 
};
